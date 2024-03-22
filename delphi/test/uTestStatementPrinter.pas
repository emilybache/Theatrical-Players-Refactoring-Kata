unit uTestStatementPrinter;

interface

uses
  System.SysUtils,
  DUnitX.TestFramework,
  clrInvoice,
  clrPlay,
  clrPerformance,
  clrStatementPrinter;

type
  [TestFixture]
  TTestStatementPrinter = class
  public
    [Test]
    procedure ExampleStatement;

    [Test]
    procedure StatementWithNewPlayTypes;
  end;

implementation

procedure TTestStatementPrinter.ExampleStatement;
var
  Actual: string;
  Invoice: TInvoice;
  Plays: TPlays;
  Performances: TPerformances;
const
  Expected = '''
  Statement for BigCo
    Hamlet: $650.00 (55 seats)
    As You Like It: $580.00 (35 seats)
    Othello: $500.00 (40 seats)
  Amount owed is $1,730.00
  You earned 47 credits

  ''';
begin
  Performances := TPerformances.Create;
  Plays := TPlays.Create;
  Invoice := TInvoice.Create('BigCo', Performances);
  try
    Plays.Add(TPlay.Create('hamlet', 'Hamlet', 'tragedy'));
    Plays.Add(TPlay.Create('as-like', 'As You Like It', 'comedy'));
    Plays.Add(TPlay.Create('othello', 'Othello', 'tragedy'));

    Performances.Add(TPerformance.Create('hamlet', 55));
    Performances.Add(TPerformance.Create('as-like', 35));
    Performances.Add(TPerformance.Create('othello', 40));

    Actual := TStatementPrinter.Print(Invoice, Plays);
    Assert.AreEqual(Expected, Actual);
  finally
    Invoice.Free;
    Plays.Free;
    Performances.Free;
  end;
end;

procedure TTestStatementPrinter.StatementWithNewPlayTypes;
var
  Actual: string;
  Invoice: TInvoice;
  Plays: TPlays;
  Performances: TPerformances;
begin
  Performances := TPerformances.Create;
  Plays := TPlays.Create;
  Invoice := TInvoice.Create('BigCo', Performances);
  try
    Plays.Add(TPlay.Create('henry-v', 'Henry V', 'history'));
    Plays.Add(TPlay.Create('as-like', 'As You Like It', 'pastoral'));

    Performances.Add(TPerformance.Create('henry-v', 53));
    Performances.Add(TPerformance.Create('as-like', 55));

    Assert.WillRaise(
      procedure
      begin
        TStatementPrinter.Print(Invoice, Plays);
      end, Exception, 'unknown type: ' + 'henry-v'
    );
  finally
    Invoice.Free;
    Plays.Free;
    Performances.Free;
  end;
end;

initialization
  TDUnitX.RegisterTestFixture(TTestStatementPrinter);

end.

