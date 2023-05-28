import math
#
AUDIENCE = 'audience'
TYPE = 'type'
PLAYID = 'playID'
PERFORMANCES = 'performances'

EQUAL_FUNC2 = 20
EQUAL_FUNC = 30
PERSENTAGE = 100
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

    for perf in invoice[PERFORMANCES]:
        play = plays[perf[PLAYID]]
        if play[TYPE] == TRAGEDY:
            this_amount = FOURTHOUS
            this_amount = AUDIENCE_FUNC(perf, this_amount)
        elif play[TYPE] == COMEDY:
            this_amount = THREETHOUS
            this_amount = AUDIENCE_FUNC2(perf, this_amount)
            this_amount += 300 * perf[AUDIENCE]
        else:
            raise ValueError(f'unknown type: {play["type"]}')

        volume_credits += max(perf[AUDIENCE] - EQUAL_FUNC, 0)

        volume_credits = GET_COMEDY(perf, play, volume_credits)

        result += f' {play["name"]}: {format_as_dollars(this_amount / PERSENTAGE)} ({perf["audience"]} seats)\n'
        total_amount += this_amount

    result += f'Amount owed is {format_as_dollars(total_amount / PERSENTAGE)}\n'
    result += f'You earned {volume_credits} credits\n'
    return result


def AUDIENCE_FUNC2(perf, this_amount):
    if perf[AUDIENCE] > EQUAL_FUNC2:
        this_amount += 10000 + 500 * (perf[AUDIENCE] - EQUAL_FUNC2)
    return this_amount


def AUDIENCE_FUNC(perf, this_amount):
    if perf[AUDIENCE] > EQUAL_FUNC:
        this_amount += 1000 * (perf[AUDIENCE] - EQUAL_FUNC)
    return this_amount


def GET_COMEDY(perf, play, volume_credits):
    if COMEDY == play[TYPE]:
        volume_credits += math.floor(perf[AUDIENCE] / 5)
    return volume_credits


