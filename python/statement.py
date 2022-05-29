import copy
import math


# Public
def statement(invoice, plays):
    statement_data = _create_statement_data(invoice,plays)
    return _get_statement(statement_data)


# Implementation
def _get_statement(data: object) -> object:
    # Inner helper function
    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    # Code to create statement text
    result = f'Statement for {data["customer"]}\n'

    for perf in data['performances']:
        # print line for this order
        result += f' {perf["play"]["name"]}: {format_as_dollars(perf["amount"] / 100)} ({perf["audience"]} seats)\n'

    result += f'Amount owed is {format_as_dollars(data["totalAmount"] / 100)}\n'
    result += f'You earned {data["totalVolumeCredits"]} credits\n'
    return result


def _create_statement_data(invoice, plays):
    # Inner helper functions
    def map_performance(perf):
        # creating a copy of perf without copying reference, result = perf creates a deep copy
        result = copy.copy(perf)
        result['play'] = get_play_for(result)
        result['amount'] = get_amount_for(result)
        result['volumeCredits'] = get_volume_credits_for(result)
        return result

    def get_play_for(performance):
        return plays[performance['playID']]

    def get_amount_for(performance):
        print(performance)
        play_type = performance['play']['type']
        if play_type == "tragedy":
            amount = 40000
            if performance['audience'] > 30:
                amount += 1000 * (performance['audience'] - 30)
        elif play_type == "comedy":
            amount = 30000
            if performance['audience'] > 20:
                amount += 10000 + 500 * (performance['audience'] - 20)

            amount += 300 * performance['audience']
        else:
            raise ValueError(f'unknown type: {play_type}')

        return amount

    def get_volume_credits_for(performance):
        # add volume credits
        vol_credits = 0
        vol_credits += max(performance['audience'] - 30, 0)
        # add extra credit for every ten comedy attendees
        if "comedy" == performance['play']["type"]:
            vol_credits += math.floor(performance['audience'] / 5)

        return vol_credits

    def get_total_amount(data):
        total_amount = 0
        for performance in data['performances']:
            total_amount += performance['amount']

        return total_amount

    def get_total_volume_credits(data):
        total_volume_credits = 0
        for performance in data['performances']:
            total_volume_credits += performance['volumeCredits']

        return total_volume_credits

    statement_data = {'customer': invoice['customer'],
                      'performances': list(map(map_performance, invoice['performances']))}
    statement_data['totalAmount'] = get_total_amount(statement_data)
    statement_data['totalVolumeCredits'] = get_total_volume_credits(statement_data)

    return statement_data
