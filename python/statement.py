import json
import math


# Public
def statement(invoice, plays):
    total_amount = 0
    volume_credits = 0
    result = f'Statement for {invoice["customer"]}\n'

    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    def _get_play_for(performance):
        return plays[performance['playID']]

    def _get_amount_for(performance):
        play_type = _get_play_for(performance)['type']
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

    def _get_volume_credits_for(performance):
        # add volume credits
        vol_credits = 0
        vol_credits += max(performance['audience'] - 30, 0)
        # add extra credit for every ten comedy attendees
        if "comedy" == _get_play_for(performance)["type"]:
            vol_credits += math.floor(performance['audience'] / 5)

        return vol_credits

    for perf in invoice['performances']:
        # add volume credits
        volume_credits += _get_volume_credits_for(perf)
        # print line for this order
        result += f' {_get_play_for(perf)["name"]}: {format_as_dollars(_get_amount_for(perf) / 100)} ({perf["audience"]} seats)\n'
        total_amount += _get_amount_for(perf)

    result += f'Amount owed is {format_as_dollars(total_amount / 100)}\n'
    result += f'You earned {volume_credits} credits\n'
    return result


# Implementation

