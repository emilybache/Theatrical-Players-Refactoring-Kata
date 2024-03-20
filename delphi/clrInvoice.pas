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
    destructor Destroy; override;
  end;

  TInvoices = class(TObjectList<TInvoice>)
  end;

implementation

constructor TInvoice.Create(ACustomer: string; APerformances: TPerformances);
begin
  Customer := ACustomer;
  Performances := APerformances;
end;

destructor TInvoice.Destroy;
begin
  FreeAndNil(Performances);

  inherited;
end;

end.
