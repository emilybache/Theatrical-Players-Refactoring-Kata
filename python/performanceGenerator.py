import math


# Parent class
class performanceGenerator(object):
    def __init__(self, perf, play):
        self.performance = perf
        self.play = play
        self.amount = self.get_amount()
        self.volume_credits = self.get_volume_credits()

    def get_amount(self):
        pass

    def get_volume_credits(self):
        pass


# child classes
class tragedyPlay(performanceGenerator):
    def get_amount(self):
        amount = 40000
        if self.performance['audience'] > 30:
            amount += 1000 * (self.performance['audience'] - 30)
        return amount

    def get_volume_credits(self):
        return max(self.performance['audience'] - 30, 0)


class comedyPlay(performanceGenerator):
    def get_amount(self):
        amount = 30000
        if self.performance['audience'] > 20:
            amount += 10000 + 500 * (self.performance['audience'] - 20)

        amount += 300 * self.performance['audience']

        return amount

    def get_volume_credits(self):
        return max(self.performance['audience'] - 30, 0) + math.floor(self.performance['audience'] / 5)
