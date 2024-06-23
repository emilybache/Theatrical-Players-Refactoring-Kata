package theatricalplays;

import java.text.NumberFormat;
import java.util.Locale;
import java.util.Map;

public class StatementPrinter {

    public String print(Invoice invoice, Map<String, Play> plays) {
        var result = String.format("Statement for %s\n", invoice.customer);

        for (var perf : invoice.performances) {
            // print line for this order
            result += String.format("  %s: %s (%s seats)\n", playForPerformance(plays, perf).name,
                    formatAsUSD(amountFor(perf, playForPerformance(plays, perf))),
                    perf.audience);
        }

        result += String.format("Amount owed is %s\n", formatAsUSD(totalAmountFor(new StatementData(invoice, plays))));
        result += String.format("You earned %s credits\n", totalVolumeCredits(invoice, plays));
        return result;
    }

    private static int totalAmountFor(StatementData statementData) {
        var totalAmount = 0;
        for (var perf : statementData.invoice().performances) {
            totalAmount += amountFor(perf, playForPerformance(statementData.plays(), perf));
        }
        return totalAmount;
    }

    private static int totalVolumeCredits(Invoice invoice, Map<String, Play> plays) {
        var volumeCredits = 0;
        for (var perf : invoice.performances) {
            volumeCredits += volumeCreditsFor(perf, playForPerformance(plays, perf));
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

    private static int volumeCreditsFor(Performance perf, Play play) {
        var result = 0;
        // add volume credits
        result += Math.max(perf.audience - 30, 0);
        // add extra credit for every ten comedy attendees
        if ("comedy".equals(play.type)) result += Math.floor(perf.audience / 5);
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
