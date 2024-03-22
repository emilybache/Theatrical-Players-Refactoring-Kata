unit clrStatementPrinter;

interface

uses
  Windows,
  SysUtils,
  StrUtils,
  Math,
  clrInvoice,
  clrPlay,
  clrPerformance;

type
  TStatementPrinter = class(TObject)
  private
    class function FormatCurrency(AValue: Double): string; static;
  public
    class function Print(AInvoice: TInvoice; APlays: TPlays): string;
  end;

implementation

class function TStatementPrinter.FormatCurrency(AValue: Double): string;
var
  Format: TFormatSettings;
begin
  Format.DecimalSeparator := '.';
  Format.ThousandSeparator := ',';
  Result := FormatFloat('$#,##0.00', AValue, Format);
end;

class function TStatementPrinter.Print(AInvoice: TInvoice; APlays: TPlays): string;
var
  TotalAmount: Integer;
  VolumeCredits: Integer;
  ThisAmount: Integer;
  Play: TPlay;
  Performance: TPerformance;
begin
  TotalAmount := 0;
  VolumeCredits := 0;
  Result := Format('Statement for %s'#13#10, [AInvoice.Customer]);

  for Performance in AInvoice.Performances do
  begin
    Play := APlays.GetItemByPlayId(Performance.PlayId);
    ThisAmount := 0;

    if ( Play.&Type = 'tragedy' ) then
    begin
      ThisAmount := 40000;
      if ( Performance.Audience > 30 ) then
        ThisAmount := ThisAmount + 1000 * (Performance.Audience - 30);
     end

    else if ( Play.&Type = 'comedy' ) then
    begin
      ThisAmount := 30000;
      if (Performance.Audience > 20) then
          ThisAmount := ThisAmount + 10000 + 500 * (Performance.Audience - 20);
      ThisAmount := ThisAmount + 300 * Performance.Audience;
    end

    else
      raise Exception.Create(Format('unknown type: %s', [Play.&Type]));

    // add volume credits
    VolumeCredits := VolumeCredits + Math.max(Performance.Audience - 30, 0);

    // add extra credit for every ten comedy attendees
    if ( 'comedy'.equals(play.&type) ) then
      VolumeCredits := VolumeCredits + Math.floor(Performance.Audience / 5);

    // print line for this order
    Result := Result + Format('  %s: %s (%d seats)'#13#10, [Play.Name, FormatCurrency(ThisAmount / 100), Performance.Audience]);
    TotalAmount := TotalAmount + ThisAmount;
  end;

  Result := Result + Format('Amount owed is %s'#13#10, [FormatCurrency(TotalAmount / 100)]);
  Result := Result + Format('You earned %d credits'#13#10, [VolumeCredits]);
end;

end.
