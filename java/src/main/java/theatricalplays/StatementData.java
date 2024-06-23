package theatricalplays;

import java.util.List;
import java.util.Map;

public final class StatementData {
    private final Invoice invoice;
    private final Map<String, Play> plays;

    public StatementData(Invoice invoice, Map<String, Play> plays) {
        this.invoice = invoice;
        this.plays = plays;
    }

    Play playForPerformance(Performance perf) {
        return plays.get(perf.playID);
    }

    PerformanceData getPerformanceData(Performance perf) {
        return new PerformanceData(perf, plays.get(perf.playID));
    }

    List<Performance> getPerformances() {
        return invoice.performances;
    }

    public Map<String, Play> getPlays() {
        return plays;
    }

    public Invoice getInvoice() {
        return invoice;
    }
}