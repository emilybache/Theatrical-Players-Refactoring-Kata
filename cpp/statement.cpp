#include "statement.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// https://stackoverflow.com/a/7277333/104370
class comma_numpunct : public std::numpunct<char>
{
  protected:
    virtual char do_thousands_sep() const override
    {
        return ',';
    }

    virtual std::string do_grouping() const override
    {
        return "\03";
    }
};

const string types_of_performances[2] = {"tragedy", "comedy"};

std::string statement(const nlohmann::json& invoice, const nlohmann::json& plays)
{
    float total_amount = 0;
    int volume_credits = 0;

    const std::locale comma_locale(std::locale(), new comma_numpunct());

    std::stringstream result;
    result.imbue(comma_locale);
    result << "Statement for " << invoice["customer"].get<std::string>() << '\n';

    for( const nlohmann::json& perf : invoice["performances"])
    {
        float this_amount = 0;
        const nlohmann::json& play = plays[perf["playID"].get<std::string>()];
      
        switch(play["type"])
        {
          case types_of_performances[0]:
            
            this_amount = ((perf["audience"] > 30) ? (1000 * perf["audience"].get<int>() + 10000) : 40000);
            volume_credits += std::max(perf["audience"].get<int>() - 30, 0);
            break;
            
          case types_of_performances[1]:
            
            this_amount = 30000 + perf["audience"].get<int>() * ((perf["audience"] > 20) ? 500 : 300);
            volume_credits += perf["audience"].get<int>() / 5;
            break;
            
          default:
            
            volume_credits += std::max(perf["audience"].get<int>() - 30, 0);
            throw std::domain_error("unknown type: " + play["type"].get<std::string>());
            break;
        }
     
        result << " " << play["name"].get<std::string>() << ": " << "$" << std::fixed << (this_amount/100) <<
            " (" << perf["audience"] << " seats)\n";
        total_amount += this_amount;
    }

    result << "Amount owed is " << "$" << std::fixed << (total_amount/100.0f) << "\n";
    result << "You earned " << volume_credits << " credits";
    return result.str();
}
