import 'dart:math';

import 'package:intl/intl.dart';
import 'package:theatrical_plays/invoice.dart';
import 'package:theatrical_plays/play.dart';

class StatementPrinter {

  String print(Invoice invoice, Map<String, Play> plays) {
    var totalAmount = 0;
    var volumeCredits = 0;
    var result = 'Statement for ${invoice.customer}\n';

    final frmt = NumberFormat.currency(locale: 'en_US', symbol: '\$');

    for (var perf in invoice.performances) {
      final play = plays[perf.playID];
      var thisAmount = 0;

      switch (play!.type) {
        case 'tragedy':
          thisAmount = 40000;
          if (perf.audience > 30) {
            thisAmount += 1000 * (perf.audience - 30);
          }
          break;
        case 'comedy':
          thisAmount = 30000;
          if (perf.audience > 20) {
            thisAmount += 10000 + 500 * (perf.audience - 20);
          }
          thisAmount += 300 * perf.audience;
          break;
        default:
          throw Exception('unknown type: ${play.type}');
      }

      // add volume credits
      volumeCredits += max(perf.audience - 30, 0);
      // add extra credit for every ten comedy attendees
      if ('comedy' == play.type) volumeCredits += (perf.audience ~/ 5).floor();

      // print line for this order
      result += '  ${play.name}: ${frmt.format(thisAmount ~/ 100)} (${perf.audience} seats)\n';
      totalAmount += thisAmount;
    }
    result += 'Amount owed is ${frmt.format(totalAmount ~/ 100)}\n';
    result += 'You earned $volumeCredits credits\n';
    return result;
  }
}