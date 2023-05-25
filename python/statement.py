import math


class statement(object):
    def __init__(self):
        self.total_amount = 0
        self.volume_credits = 0
        self.result = ''

    @staticmethod
    def tragedy(perf):
        amount = 40000
        if perf['audience'] > 30:
            amount += 1000 * (perf['audience'] - 30)
        return amount

    @staticmethod
    def comedy(perf):
        amount = 30000
        if perf['audience'] > 20:
            amount += 10000 + 500 * (perf['audience'] - 20)
        amount += 300 * perf['audience']
        return amount

    @staticmethod
    def format_as_dollars(amount):
        return f"${amount:0,.2f}"

    def upd_volume_credits(self, perf, play):
        self.volume_credits += max(perf['audience'] - 30, 0)
        if "comedy" == play["type"]:
            self.volume_credits += math.floor(perf['audience'] / 5)

    def statement(self, invoice, plays):
        self.result = f'Statement for {invoice["customer"]}\n'
        for perf in invoice['performances']:
            play = plays[perf['playID']]
            if play['type'] == "tragedy":
                this_amount = self.tragedy(perf)
            elif play['type'] == "comedy":
                this_amount = self.comedy(perf)
            else:
                raise ValueError(f'unknown type: {play["type"]}')
            self.upd_volume_credits(perf, play)
            self.result += f' {play["name"]}: {self.format_as_dollars(this_amount / 100)} ({perf["audience"]} seats)\n'
            self.total_amount += this_amount

        self.result += f'Amount owed is {self.format_as_dollars(self.total_amount / 100)}\n'
        self.result += f'You earned {self.volume_credits} credits\n'
        return self.result
