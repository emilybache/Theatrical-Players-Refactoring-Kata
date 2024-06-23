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

    int totalAmount() {
        var totalAmount = 0;
        for (var perf : getPerformances()) {
            totalAmount += getPerformanceData(perf).amount();
        }
        return totalAmount;
    }

    int totalVolumeCredits() {
        var volumeCredits = 0;
        for (var perf : getPerformances()) {
            volumeCredits += getPerformanceData(perf).volumeCredits();
        }
        return volumeCredits;
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