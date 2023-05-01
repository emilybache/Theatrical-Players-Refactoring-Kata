import math

EQUAL_FUNC2 = 20
EQUAL_FUNC = 30
HANDR = 100
THREETHOUS = 30000
FOURTHOUS = 40000

COMEDY = "comedy"
TRAGEDY = "tragedy"

def statement(invoice, plays):
    total_amount = 0
    volume_credits = 0
    result = f'Statement for {invoice["customer"]}\n'

    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    for perf in invoice['performances']:
        play = plays[perf['playID']]
        if play['type'] == TRAGEDY:
            this_amount = FOURTHOUS
            this_amount = AUDIENCE_FUNC(perf, this_amount)
        elif play['type'] == COMEDY:
            this_amount = THREETHOUS
            this_amount = AUDIENCE_FUNC2(perf, this_amount)
            this_amount += 300 * perf['audience']
        else:
            raise ValueError(f'unknown type: {play["type"]}')

        volume_credits += max(perf['audience'] - EQUAL_FUNC, 0)

        volume_credits = GET_COMEDY(perf, play, volume_credits)

        result += f' {play["name"]}: {format_as_dollars(this_amount / HANDR)} ({perf["audience"]} seats)\n'
        total_amount += this_amount

    result += f'Amount owed is {format_as_dollars(total_amount / HANDR)}\n'
    result += f'You earned {volume_credits} credits\n'
    return result


def AUDIENCE_FUNC2(perf, this_amount):
    if perf['audience'] > EQUAL_FUNC2:
        this_amount += 10000 + 500 * (perf['audience'] - EQUAL_FUNC2)
    return this_amount


def AUDIENCE_FUNC(perf, this_amount):
    if perf['audience'] > EQUAL_FUNC:
        this_amount += 1000 * (perf['audience'] - EQUAL_FUNC)
    return this_amount


def GET_COMEDY(perf, play, volume_credits):
    if COMEDY == play["type"]:
        volume_credits += math.floor(perf['audience'] / 5)
    return volume_credits


