import math


def statement(invoice, plays):
    # Inner helper functions
    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    def get_play_for(performance):
        return plays[performance['playID']]

    def get_amount_for(performance):
        play_type = get_play_for(performance)['type']
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
        if "comedy" == get_play_for(performance)["type"]:
            vol_credits += math.floor(performance['audience'] / 5)

        return vol_credits

    def get_total_amount():
        total_amount = 0
        for performance in invoice['performances']:
            total_amount += get_amount_for(performance)

        return total_amount

    def get_total_volume_credits():
        total_volume_credits = 0
        for performance in invoice['performances']:
            total_volume_credits += get_volume_credits_for(performance)

        return total_volume_credits

    # main statement function code
    result = f'Statement for {invoice["customer"]}\n'

    for perf in invoice['performances']:
        # print line for this order
        result += f' {get_play_for(perf)["name"]}: {format_as_dollars(get_amount_for(perf) / 100)} ({perf["audience"]} seats)\n'

    result += f'Amount owed is {format_as_dollars(get_total_amount() / 100)}\n'
    result += f'You earned {get_total_volume_credits()} credits\n'
    return result
