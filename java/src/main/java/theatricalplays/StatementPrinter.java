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
            result += String.format("  %s: %s (%s seats)\n", statementData.playForPerformance(statementData.getPlays(), perf).name,
                    formatAsUSD(statementData.getPerformanceData(perf).amount()),
                    perf.audience);
        }

        result += String.format("Amount owed is %s\n", formatAsUSD(totalAmountFor(statementData)));
        result += String.format("You earned %s credits\n", totalVolumeCredits(statementData));
        return result;
    }

    private static int totalAmountFor(StatementData statementData) {
        var totalAmount = 0;
        for (var perf : statementData.getPerformances()) {
            totalAmount += statementData.getPerformanceData(perf).amount();
        }
        return totalAmount;
    }

    private static int totalVolumeCredits(StatementData statementData) {
        var volumeCredits = 0;
        for (var perf : statementData.getPerformances()) {
            volumeCredits += statementData.getPerformanceData(perf).volumeCredits();
        }
        return volumeCredits;
    }

    private static String formatAsUSD(int amount) {
        NumberFormat frmt = NumberFormat.getCurrencyInstance(Locale.US);
        return frmt.format(amount / 100);
    }

}
