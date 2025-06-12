require "minitest/autorun"
require "json"
require_relative "../lib/theatrical_plays/statement_printer"

class TestStatementPrinter < Minitest::Test
  def test_statement_with_known_types
    invoice = load_json_fixture('invoice.json')
    plays = load_json_fixture('plays.json')

    expected_statement = "Statement for BigCo\n" \
    " Hamlet: $650.00 (55 seats)\n" \
    " As You Like It: $580.00 (35 seats)\n" \
    " Othello: $500.00 (40 seats)\n" \
    "Amount owed is $1730.00\n" \
    "You earned 47 credits\n"

    assert_equal expected_statement, TheatricalPlays::StatementPrinter.new.print(invoice, plays)
  end

  def test_statement_with_new_types
    invoice = load_json_fixture('invoice_new_plays.json')
    plays = load_json_fixture('new_plays.json')

    error = assert_raises(StandardError) do
      TheatricalPlays::StatementPrinter.new.print(invoice, plays)
    end

    assert_equal 'unknown type: history', error.message
  end

  private

  def load_json_fixture(filename)
    file_path = File.join(__dir__, 'data', filename)
    JSON.parse(File.read(file_path))
  end
end
