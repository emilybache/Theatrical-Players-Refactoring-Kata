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
                    formatAsUSD(amountFor(perf, playForPerformance(statementData.getPlays(), perf))),
                    perf.audience);
        }

        result += String.format("Amount owed is %s\n", formatAsUSD(totalAmountFor(statementData)));
        result += String.format("You earned %s credits\n", totalVolumeCredits(statementData));
        return result;
    }

    private static int totalAmountFor(StatementData statementData) {
        var totalAmount = 0;
        for (var perf : statementData.getPerformances()) {
            totalAmount += amountFor(perf, playForPerformance(statementData.getPlays(), perf));
        }
        return totalAmount;
    }

    private static int totalVolumeCredits(StatementData statementData) {
        var volumeCredits = 0;
        for (var perf : statementData.getPerformances()) {
            volumeCredits += volumeCreditsFor(new PerformanceData(perf, playForPerformance(statementData.getPlays(), perf)));
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

    private static int volumeCreditsFor(PerformanceData performanceData) {
        var result = 0;
        // add volume credits
        result += Math.max(performanceData.perf().audience - 30, 0);
        // add extra credit for every ten comedy attendees
        if ("comedy".equals(performanceData.play().type)) result += Math.floor(performanceData.perf().audience / 5);
        return result;
    }

    private static int amountFor(Performance perf, Play play) {
        int result;
        switch (play.type) {
            case "tragedy":
                result = 40000;
                if (perf.audience > 30) {
                    result += 1000 * (perf.audience - 30);
                }
                break;
            case "comedy":
                result = 30000;
                if (perf.audience > 20) {
                    result += 10000 + 500 * (perf.audience - 20);
                }
                result += 300 * perf.audience;
                break;
            default:
                throw new Error("unknown type: ${play.type}");
        }
        return result;
    }

}
