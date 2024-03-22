unit clrPerformance;

interface

uses
  System.Generics.Collections;

type
  TPerformance = class(TObject)
  public
    PlayId: string;
    Audience: Integer;

    constructor Create(APlayId: string; AAudience: Integer);
  end;

  TPerformances = class(TObjectList<TPerformance>)
  end;

implementation

constructor TPerformance.Create(APlayId: string; AAudience: Integer);
begin
  inherited Create;

  PlayId := APlayId;
  Audience := AAudience;
end;

end.
