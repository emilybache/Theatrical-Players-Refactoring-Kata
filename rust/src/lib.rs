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
