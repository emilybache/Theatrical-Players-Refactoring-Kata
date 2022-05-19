const statement = require("../src/statement");
const fs = require("fs");

test("example statement", () => {
  const invoice = JSON.parse(
    fs.readFileSync("test/mocks/invoice.json", "utf8")
  );
  const plays = JSON.parse(fs.readFileSync("test/mocks/plays.json", "utf8"));
  expect(statement(invoice, plays)).toMatchSnapshot();
});

test("statement with new play types", () => {
  const invoice = JSON.parse(
    fs.readFileSync("test/mocks/invoice_new_plays.json", "utf8")
  );
  const plays = JSON.parse(
    fs.readFileSync("test/mocks/new_plays.json", "utf8")
  );
  expect(() => {
    statement(invoice, plays);
  }).toThrow(/unknown type/);
});

test("statement with underperformed plays", () => {
  const invoice = JSON.parse(
    fs.readFileSync("test/mocks/invoice_less_audience.json", "utf8")
  );
  const plays = JSON.parse(fs.readFileSync("test/mocks/plays.json", "utf8"));
  expect(statement(invoice, plays)).toMatchSnapshot();
});
