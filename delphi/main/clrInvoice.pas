unit clrInvoice;

interface

uses
  System.SysUtils,
  System.Generics.Collections,
  clrPerformance;

type
  TInvoice = class(TObject)
  public
    Customer: string;
    Performances: TPerformances;

    constructor Create(ACustomer: string; APerformances: TPerformances);
  end;

  TInvoices = class(TObjectList<TInvoice>)
  end;

implementation

constructor TInvoice.Create(ACustomer: string; APerformances: TPerformances);
begin
  inherited Create;

  Customer := ACustomer;
  Performances := APerformances;
end;

end.
