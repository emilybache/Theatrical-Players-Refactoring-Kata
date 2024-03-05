#[cfg(test)]
mod tests {
    use insta::assert_snapshot;
    use serde_json::json;
    use theatrical_players::statement;

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
        });
        let result = statement(invoice, plays);
        assert_snapshot!(result, @r###"
                        Statement for BigCo
                         Hamlet: $650.00 (55 seats)
                         As You Like It: $580.00 (35 seats)
                         Othello: $500.00 (40 seats)
                        Amount owed is $1,730.00
                        You earned 47 credits
                        "###);
    }

    #[test]
    #[should_panic(expected = "unknown type")]
    fn statement_with_new_play_types() {
        let invoice = json!({
            "customer": "BigCoII",
            "performances":[
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
