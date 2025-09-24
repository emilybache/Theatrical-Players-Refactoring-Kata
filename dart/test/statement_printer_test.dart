import 'package:test/test.dart';
import 'package:theatrical_plays/invoice.dart';
import 'package:theatrical_plays/performance.dart';
import 'package:theatrical_plays/play.dart';
import 'package:theatrical_plays/statement_printer.dart';

void main() {
  test('example statement', () {
    final plays = {
      'hamlet': Play('Hamlet', 'tragedy'),
      'as-like': Play('As You Like It', 'comedy'),
      'othello': Play('Othello', 'tragedy'),
    };

    final invoice = Invoice('BigCo', [
      Performance('hamlet', 55),
      Performance('as-like', 35),
      Performance('othello', 40),
    ]);

    final statementPrinter = StatementPrinter();
    final result = statementPrinter.print(invoice, plays);

    const expectedResult = 'Statement for BigCo\n'
        '  Hamlet: \$650.00 (55 seats)\n'
        '  As You Like It: \$580.00 (35 seats)\n'
        '  Othello: \$500.00 (40 seats)\n'
        'Amount owed is \$1,730.00\n'
        'You earned 47 credits\n';

    expect(result, expectedResult);
  });

  test('statement with new play types throws error', () {
    final plays = {
      'henry-v': Play('Henry V', 'history'),
      'as-like': Play('As You Like It', 'pastoral'),
    };

    final invoice = Invoice('BigCo', [
      Performance('henry-v', 53),
      Performance('as-like', 55),
    ]);

    final statementPrinter = StatementPrinter();
    
    expect(
      () => statementPrinter.print(invoice, plays),
      throwsA(
        isA<Exception>().having(
          (e) => e.toString(),
          'message',
          contains('unknown type: '))));
  });
}