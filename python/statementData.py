class statementData:
    def __init__(self, customer, performances):
        self.customer = customer
        # performances is the list of performanceGenerator objects
        self.performances: list = performances
        self.total_amount = self.get_total_amount()
        self.total_volume_credits = self.get_total_volume_credits()

    def get_total_amount(self):
        total_amount = 0
        for perf in self.performances:
            total_amount += perf.amount

        return total_amount

    def get_total_volume_credits(self):
        total_volume_credits = 0
        for performance in self.performances:
            total_volume_credits += performance.volume_credits

        return total_volume_credits
