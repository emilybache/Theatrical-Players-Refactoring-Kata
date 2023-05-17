import math

AUDIENCE_20 = 20
AUDIENCE_30 = 30

AMOUNT_30000 = 30000
AMOUNT_40000 = 40000
AMOUNT_10000 = 10000
AMOUNT_1000 = 1000
AMOUNT_500 = 500
AMOUNT_300 = 300

TRAGEDY = "tragedy"
COMEDY = "comedy"


def calculate_tragedy(audience):
    this_amount = AMOUNT_40000
    if audience > AUDIENCE_30:
        this_amount += AMOUNT_1000 * (audience - AUDIENCE_30)
    return this_amount


def calculate_comedy(audience):
    this_amount = AMOUNT_30000
    if audience > AUDIENCE_20:
        this_amount += AMOUNT_10000 + AMOUNT_500 * (audience - AUDIENCE_20)
    this_amount += AMOUNT_300 * audience
    return this_amount


def calculate_amount(play, audience):
    if play['type'] == TRAGEDY:
        this_amount = calculate_tragedy(audience)
    elif play['type'] == COMEDY:
        this_amount = calculate_comedy(audience)
    else:
        raise ValueError(f'unknown type: {play["type"]}')
    return this_amount


def calculate_volume_credits(audience, play, volume_credits):
    # add volume credits
    volume_credits += max(audience - AUDIENCE_30, 0)
    # add extra credit for every ten comedy attendees
    if COMEDY == play["type"]:
        volume_credits += math.floor(audience / 5)
    return volume_credits


def format_as_dollars(amount):
    return f"${amount:0,.2f}"


def statement(invoice, plays):
    total_amount = 0
    volume_credits = 0
    result = f'Statement for {invoice["customer"]}\n'

    for perf in invoice['performances']:
        play = plays[perf['playID']]
        audience = perf['audience']
        play_name = play["name"]
        this_amount = calculate_amount(play, audience)
        volume_credits = calculate_volume_credits(audience, play, volume_credits)
        # print line for this order
        result += f' {play_name}: {format_as_dollars(this_amount / 100)} ({audience} seats)\n'
        total_amount += this_amount

    result += f'Amount owed is {format_as_dollars(total_amount / 100)}\nYou earned {volume_credits} credits\n'
    return result