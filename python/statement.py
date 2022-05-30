from create_statement_data import create_statement_data


# Public
def statement(invoice, plays):
    statement_data = create_statement_data(invoice,plays)
    return _get_statement(statement_data)


# Implementation
def _get_statement(data: object) -> object:
    # Inner helper function
    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    # Code to create statement text
    result = f'Statement for {data.customer}\n'

    for perf in data.performances:
        # print line for this order
        result += f' {perf.play["name"]}: {format_as_dollars(perf.amount / 100)} ({perf.performance["audience"]} seats)\n'

    result += f'Amount owed is {format_as_dollars(data.total_amount / 100)}\n'
    result += f'You earned {data.total_volume_credits} credits\n'
    return result

