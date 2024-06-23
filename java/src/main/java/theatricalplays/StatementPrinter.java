package theatricalplays;

import java.text.NumberFormat;
import java.util.Locale;
import java.util.Map;

public class StatementPrinter {

    public String print(Invoice invoice, Map<String, Play> plays) {
        StatementData statementData = new StatementData(invoice, plays);

        var result = String.format("Statement for %s\n", statementData.getInvoice().customer);

        for (var perf : statementData.getPerformances()) {
            // print line for this order
            result += String.format("  %s: %s (%s seats)\n", playForPerformance(statementData.getPlays(), perf).name,
                    formatAsUSD(new PerformanceData(perf, playForPerformance(statementData.getPlays(), perf)).amount()),
                    perf.audience);
        }

        result += String.format("Amount owed is %s\n", formatAsUSD(totalAmountFor(statementData)));
        result += String.format("You earned %s credits\n", totalVolumeCredits(statementData));
        return result;
    }

    private static int totalAmountFor(StatementData statementData) {
        var totalAmount = 0;
        for (var perf : statementData.getPerformances()) {
            totalAmount += new PerformanceData(perf, playForPerformance(statementData.getPlays(), perf)).amount();
        }
        return totalAmount;
    }

    private static int totalVolumeCredits(StatementData statementData) {
        var volumeCredits = 0;
        for (var perf : statementData.getPerformances()) {
            volumeCredits += new PerformanceData(perf, playForPerformance(statementData.getPlays(), perf)).volumeCredits();
        }
        return volumeCredits;
    }

    private static String formatAsUSD(int amount) {
        NumberFormat frmt = NumberFormat.getCurrencyInstance(Locale.US);
        return frmt.format(amount / 100);
    }

    private static Play playForPerformance(Map<String, Play> plays, Performance perf) {
        return plays.get(perf.playID);
    }

}
