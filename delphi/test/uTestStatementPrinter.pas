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
    procedure TestTragedy;

    [Test]
    procedure TestComedy;

    [Test]
    procedure TestUnknownPlay;

    [Test]
    procedure TestMultiplePerformances;
  end;

implementation

procedure TTestStatementPrinter.TestTragedy;
var
  Actual: string;
  Invoice: TInvoice;
  Plays: TPlays;
  Performances: TPerformances;
const
  Expected = '''
  Statement for BigCo
    Hamlet: $650.00 (55 seats)
  Amount owed is $650.00
  You earned 25 credits

  ''';
begin
  Performances := TPerformances.Create;
  Performances.Add(TPerformance.Create('hamlet', 55));

  Invoice := TInvoice.Create('BigCo', Performances);

  Plays := TPlays.Create;
  Plays.Add(TPlay.Create('hamlet', 'Hamlet', 'tragedy'));

  Actual := TStatementPrinter.Print(Invoice, Plays);
  Assert.AreEqual(Expected, Actual);
end;

procedure TTestStatementPrinter.TestComedy;
var
  Actual: string;
  Invoice: TInvoice;
  Plays: TPlays;
  Performances: TPerformances;
const
  Expected = '''
  Statement for BigCo
    As You Like It: $580.00 (35 seats)
  Amount owed is $580.00
  You earned 12 credits

  ''';
begin
  Performances := TPerformances.Create;
  Performances.Add(TPerformance.Create('as-like', 35));

  Invoice := TInvoice.Create('BigCo', Performances);

  Plays := TPlays.Create;
  Plays.Add(TPlay.Create('as-like', 'As You Like It', 'comedy'));

  Actual := TStatementPrinter.Print(Invoice, Plays);
  Assert.AreEqual(Expected, Actual);
end;

procedure TTestStatementPrinter.TestUnknownPlay;
var
  Actual: string;
  Invoice: TInvoice;
  Plays: TPlays;
  Performances: TPerformances;
const
  UnknownPlay = 'unknown-play';
  UnknownType = 'unknown-type';
begin
  Performances := TPerformances.Create;
  Performances.Add(TPerformance.Create(UnknownPlay, 10));

  Invoice := TInvoice.Create('BigCo', Performances);

  Plays := TPlays.Create;
  Plays.Add(TPlay.Create(UnknownPlay, 'Unknown Play', UnknownType));

  Assert.WillRaise(
    procedure
    begin
      TStatementPrinter.Print(Invoice, Plays);
    end, Exception, 'unknown type: ' + UnknownType
  );
end;

procedure TTestStatementPrinter.TestMultiplePerformances;
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
  Performances.Add(TPerformance.Create('hamlet', 55));
  Performances.Add(TPerformance.Create('as-like', 35));
  Performances.Add(TPerformance.Create('othello', 40));

  Invoice := TInvoice.Create('BigCo', Performances);

  Plays := TPlays.Create;
  Plays.Add(TPlay.Create('hamlet', 'Hamlet', 'tragedy'));
  Plays.Add(TPlay.Create('as-like', 'As You Like It', 'comedy'));
  Plays.Add(TPlay.Create('othello', 'Othello', 'tragedy'));

  Actual := TStatementPrinter.Print(Invoice, Plays);
  Assert.AreEqual(Expected, Actual);
end;

initialization
  TDUnitX.RegisterTestFixture(TTestStatementPrinter);

end.

