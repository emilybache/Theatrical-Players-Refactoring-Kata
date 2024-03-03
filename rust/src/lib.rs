use std::cmp::max;

use currency_rs::{Currency, CurrencyOpts};
use serde_json::Value;

fn usd(value: f64) -> Currency {
    let otp = CurrencyOpts::new().set_symbol("$").set_precision(2);
    Currency::new_float(value, Some(otp))
}

pub fn statement(invoice: Value, plays: Value) -> String {
    let mut total_amount = 0;
    let mut volume_credits = 0;
    let mut result = format!("Statement for {}\n", invoice["customer"].as_str().unwrap());

    for perf in invoice["performances"].as_array().unwrap() {
        let play = &plays[perf["playID"].as_str().unwrap()];
        let mut this_amount;
        match play["type"].as_str().unwrap() {
            "tragedy" => {
                this_amount = 40000;
                if perf["audience"].as_u64().unwrap() > 30 {
                    this_amount += 1000 * (perf["audience"].as_u64().unwrap() - 30);
                }
            }
            "comedy" => {
                this_amount = 30000;
                if perf["audience"].as_u64().unwrap() > 20 {
                    this_amount += 10000 + 500 * (perf["audience"].as_u64().unwrap() - 20);
                }
                this_amount += 300 * perf["audience"].as_u64().unwrap();
            }
            play_type => {
                panic!("unknown type:{}", play_type);
            }
        }
        // add volume credits
        volume_credits += max(perf["audience"].as_u64().unwrap() - 30, 0);
        // add extra credit for every ten comedy attendees
        if "comedy" == play["type"].as_str().unwrap() {
            volume_credits += (perf["audience"].as_f64().unwrap() / 5.0).floor() as u64;
        }
        // print line for this order
        result += &format!(
            " {}: {} ({} seats)\n",
            play["name"].as_str().unwrap(),
            usd(this_amount as f64 / 100 as f64).format(),
            perf["audience"].as_u64().unwrap()
        );
        total_amount += this_amount;
    }
    result += &format!(
        "Amount owed is {}\n",
        usd(total_amount as f64 / 100 as f64).format()
    );
    result += &format!("You earned {} credits\n", volume_credits);
    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn example_statement() {
        let invoice = json!({
          "customer": "BigCo",
          "performances": [
            {
              "playID": "hamlet",
              "audience": 55
            },
            {
              "playID": "as-like",
              "audience": 35
            },
            {
              "playID": "othello",
              "audience": 40
            }
          ]
        });

        let plays = json!({
          "hamlet": {
            "name": "Hamlet",
            "type": "tragedy"
          },
          "as-like": {
            "name": "As You Like It",
            "type": "comedy"
          },
          "othello": {
            "name": "Othello",
            "type": "tragedy"
          }
        }
        );
        let result = statement(invoice, plays);

        assert_eq!(
            result,
            r#"Statement for BigCo
 Hamlet: $650.00 (55 seats)
 As You Like It: $580.00 (35 seats)
 Othello: $500.00 (40 seats)
Amount owed is $1,730.00
You earned 47 credits
"#
        );
    }

    #[test]
    #[should_panic(expected = "unknown type")]
    fn statement_with_new_play_types() {
        let invoice = json!({
        "customer": "BigCoII",
        "performances": [
          {
            "playID": "henry-v",
            "audience": 53
          },
          {
            "playID": "as-like",
            "audience": 55
          }
          ]
        });

        let plays = json!({
          "henry-v": {"name": "Henry V", "type": "history"},
          "as-like": {"name": "As You Like It", "type": "pastoral"}
        });
        statement(invoice, plays);
    }
}
