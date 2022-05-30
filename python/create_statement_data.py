from performanceGenerator import tragedyPlay, comedyPlay
from statementData import statementData


# Public
def create_statement_data(invoice, plays):
    # Inner helper functions
    def map_performance(perf):
        perf_obj = _create_performance_generator(perf, get_play_for(perf))
        return perf_obj

    def get_play_for(performance):
        return plays[performance['playID']]

    performances = list(map(map_performance, invoice['performances']))
    statement_data = statementData(invoice['customer'], performances)
    return statement_data


# Implementation
def _create_performance_generator(perf, play):
    play_type = play['type']
    if play_type == 'tragedy':
        return tragedyPlay(perf, play)
    elif play_type == 'comedy':
        return comedyPlay(perf, play)
    else:
        raise ValueError(f'unknown type: {play_type}')
