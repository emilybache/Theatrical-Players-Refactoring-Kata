program TheatricalPlayers;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils,
  System.JSON,
  System.IOUtils,
  clrInvoice in 'clrInvoice.pas',
  clrPerformance in 'clrPerformance.pas',
  clrPlay in 'clrPlay.pas',
  clrStatementPrinter in 'clrStatementPrinter.pas',
  clrLoadData in 'clrLoadData.pas';

var
  Plays: TPlays;
  Invoices: TInvoices;
  Invoice: TInvoice;
begin
  try
    Plays := TPlays.Create;
    Invoices := TInvoices.Create;

    TLoadData.LoadPlays(Plays);
    TLoadData.LoadInvoices(Invoices);

    for Invoice in Invoices do
    begin
      Write(TStatementPrinter.Print(Invoice, Plays));
      Writeln;
    end;

    Readln;

  except
    on E: Exception do
      Writeln(E.ClassName, ': ', E.Message);
  end;
end.
