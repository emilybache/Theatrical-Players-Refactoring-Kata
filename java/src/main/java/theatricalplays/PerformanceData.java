package theatricalplays;

public final class PerformanceData {
    private final Performance perf;
    private final Play play;

    public PerformanceData(Performance perf, Play play) {
        this.perf = perf;
        this.play = play;
    }

    int amount() {
        int result;
        switch (getPlay().type) {
            case "tragedy":
                result = 40000;
                if (getPerf().audience > 30) {
                    result += 1000 * (getPerf().audience - 30);
                }
                break;
            case "comedy":
                result = 30000;
                if (getPerf().audience > 20) {
                    result += 10000 + 500 * (getPerf().audience - 20);
                }
                result += 300 * getPerf().audience;
                break;
            default:
                throw new Error("unknown type: ${play.type}");
        }
        return result;
    }

    int volumeCredits() {
        var result = 0;
        // add volume credits
        result += Math.max(getPerf().audience - 30, 0);
        // add extra credit for every ten comedy attendees
        if ("comedy".equals(getPlay().type)) result += Math.floor(getPerf().audience / 5);
        return result;
    }

    public Play getPlay() {
        return play;
    }

    public Performance getPerf() {
        return perf;
    }
}