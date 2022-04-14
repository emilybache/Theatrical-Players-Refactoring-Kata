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

std::string statement(
    const nlohmann::json& invoice,
    const nlohmann::json& plays)
{
    float total_amount = 0;
    int volume_credits = 0;

    // this creates a new locale based on the current application default
    // (which is either the one given on startup, but can be overriden with
    // std::locale::global) - then extends it with an extra facet that
    // controls numeric output.
    const std::locale comma_locale(std::locale(), new comma_numpunct());

    std::stringstream result;
    result.imbue(comma_locale);
    result.precision(2);
    result << "Statement for " << invoice["customer"].get<std::string>() << '\n';

    for( const nlohmann::json& perf : invoice["performances"])
    {
        float this_amount = 0;
        const nlohmann::json& play = plays[perf["playID"].get<std::string>()];
        if (play["type"] == "tragedy")
        {
            this_amount = 40000;
            if (perf["audience"] > 30)
            {
                this_amount += 1000 * (perf["audience"].get<int>() - 30);
            }
        }

        else if (play["type"] == "comedy")
        {
            this_amount = 30000;
            if (perf["audience"] > 20)
            {
                this_amount += 10000 + 500 * (perf["audience"].get<int>() - 20);
            }

            this_amount += 300 * perf["audience"].get<int>();
        }

        else
        {
            throw std::domain_error("unknown type: " + play["type"].get<std::string>());
        }

        // add volume credits
        volume_credits += std::max(perf["audience"].get<int>() - 30, 0);

        // add extra credit for every ten comedy attendees
        if ("comedy" == play["type"])
        {
            volume_credits += perf["audience"].get<int>() / 5;
        }

        // print line for this order
        result << " " << play["name"].get<std::string>() << ": " << "$" << std::fixed << (this_amount/100) <<
            " (" << perf["audience"] << " seats)\n";
        total_amount += this_amount;
    }

    result << "Amount owed is " << "$" << std::fixed << (total_amount/100.0f) << "\n";
    result << "You earned " << volume_credits << " credits";
    return result.str();
}
