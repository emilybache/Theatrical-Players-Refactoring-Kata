package theatricalplays;

import java.text.NumberFormat;
import java.util.Locale;
import java.util.Map;

public class StatementPrinter {

    public String print(Invoice invoice, Map<String, Play> plays) {
        var totalAmount = 0;
        var volumeCredits = 0;
        var result = String.format("Statement for %s\n", invoice.customer);

        NumberFormat frmt = NumberFormat.getCurrencyInstance(Locale.US);

        for (var perf : invoice.performances) {
            var play = plays.get(perf.playID);

            volumeCredits += volumeCreditsFor(perf, play);

            // print line for this order
            result += String.format("  %s: %s (%s seats)\n", play.name, frmt.format(amountFor(perf, play) / 100), perf.audience);
            totalAmount += amountFor(perf, play);
        }
        result += String.format("Amount owed is %s\n", frmt.format(totalAmount / 100));
        result += String.format("You earned %s credits\n", volumeCredits);
        return result;
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
