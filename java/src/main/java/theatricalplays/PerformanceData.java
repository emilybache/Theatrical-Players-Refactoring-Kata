package theatricalplays;

public final class PerformanceData {
    private final Performance perf;
    private final Play play;

    public PerformanceData(Performance perf, Play play) {
        this.perf = perf;
        this.play = play;
    }

    public Play getPlay() {
        return play;
    }

    public Performance getPerf() {
        return perf;
    }
}