unit clrLoadData;

interface

uses
  System.SysUtils,
  System.JSON,
  System.IOUtils,
  clrPlay,
  clrInvoice,
  clrPerformance;

type
  TLoadData = class(TObject)
    class procedure LoadPLays(APLays: TPlays);
    class procedure LoadInvoices(AInvoices: TInvoices);
  end;

implementation

class procedure TLoadData.LoadPLays(APLays: TPlays);
var
  PlaysJSON: TJSONObject;
begin
  PlaysJSON := TJSONObject.ParseJSONValue(TFile.ReadAllText(ExtractFilePath(ParamStr(0)) + 'plays.json')) as TJSONObject;
  for var i := 0 to PlaysJSON.Count -1 do
  begin
    APlays.Add(TPlay.Create(
      PlaysJSON.Pairs[i].JsonString.Value,
      (PlaysJSON.Pairs[i].JsonValue as TJSONObject).GetValue<string>('name'),
      (PlaysJSON.Pairs[i].JsonValue as TJSONObject).GetValue<string>('type')));
  end;

end;

class procedure TLoadData.LoadInvoices(AInvoices: TInvoices);
var
  InvoicesJSON: TJSONArray;
  PerformancesJSON: TJSONArray;
  Invoice: TJSONObject;
  Performance: TJSONObject;
  Performances: TPerformances;
begin
  InvoicesJSON := TJSONArray.ParseJSONValue(TFile.ReadAllText(ExtractFilePath(ParamStr(0)) + 'invoices.json')) as TJSONArray;
  for var value in InvoicesJSON do
  begin
    Invoice := (value as TJsonObject);
    PerformancesJSON := Invoice.Values['performances'] as TJSONArray;

    Performances := TPerformances.Create;
    for var perf in PerformancesJSON do
    begin
      Performance := (perf as TJSONObject);
      Performances.Add(TPerformance.Create(
        Performance.GetValue<string>('playID'),
        Performance.GetValue<Integer>('audience')));
    end;

    AInvoices.Add(TInvoice.Create(Invoice.GetValue('customer').ToString, Performances));
  end;

end;

end.
