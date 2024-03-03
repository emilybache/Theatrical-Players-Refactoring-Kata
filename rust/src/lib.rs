use serde_json::Value;

pub fn statement(invoice: Value, plays: Value) -> String {
    "".to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = statement(Value::Null, Value::Null);
        assert_eq!(result, "");
    }
}
