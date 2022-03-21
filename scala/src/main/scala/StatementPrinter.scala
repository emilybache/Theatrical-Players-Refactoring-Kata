import java.lang.System.lineSeparator
import java.text.NumberFormat
import java.util.Locale

class StatementPrinter {
  def print(invoice: Invoice, plays: Map[String, Play]): String = {
    var totalAmount = 0
    var volumeCredits = 0
    var result = s"Statement for ${invoice.customer}$lineSeparator"
    var culture = Locale.US

    for (perf <- invoice.performances) {
      val play = plays(perf.playId)
      var thisAmount = 0

      play.`type` match {
        case "tragedy" => {
          thisAmount = 40000
          if (perf.audience > 30)
            thisAmount += 1000 * (perf.audience - 30)
        }
        case "comedy" => {
          thisAmount = 30000
          if (perf.audience > 20)
            thisAmount += 10000 + 500 * (perf.audience - 20)
          thisAmount += 300 * perf.audience
        }
        case _ => throw new Exception("unknown type: " + play.`type`)
      }
      // add volume credits
      volumeCredits += Math.max(perf.audience - 30, 0)
      // add extra credit for every ten comedy attendees
      if ("comedy" == play.`type`) volumeCredits += Math.floor(perf.audience / 5d).toInt

      // print line for this order
      result += s"  ${play.name}: ${NumberFormat.getCurrencyInstance(culture).format((thisAmount / 100).toDouble)} (${perf.audience} seats)$lineSeparator"
      totalAmount += thisAmount;
    }
    result += s"Amount owed is ${NumberFormat.getCurrencyInstance(culture).format(totalAmount / 100d)}$lineSeparator"
    result += s"You earned ${volumeCredits} credits$lineSeparator"

    result
  }
}
