package theatricalplays;

public final class PerformanceData {
    private final Performance performance;
    private final Play play;

    public PerformanceData(Performance performance, Play play) {
        this.performance = performance;
        this.play = play;
    }

    int amount() {
        int result;
        switch (play.type) {
            case "tragedy" -> {
                result = 40000;
                if (performance.audience > 30) {
                    result += 1000 * (performance.audience - 30);
                }
            }
            case "comedy" -> {
                result = 30000;
                if (performance.audience > 20) {
                    result += 10000 + 500 * (performance.audience - 20);
                }
                result += 300 * performance.audience;
            }
            default -> throw new Error("unknown type: ${play.type}");
        }
        return result;
    }

    int volumeCredits() {
        var result = 0;
        result += Math.max(performance.audience - 30, 0);
        switch (play.type) {
            case "tragedy" -> {}
            case "comedy" -> result += Math.floor(performance.audience / 5);
            default -> throw new IllegalStateException("Unexpected value: " + play.type);
        }
        return result;
    }

}