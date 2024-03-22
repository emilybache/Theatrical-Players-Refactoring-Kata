unit clrPlay;

interface

uses
  Sysutils,
  StrUtils,
  System.Generics.Collections;

type
  TPlay = class(TObject)
  public
    PlayID: string;
    Name: string;
    &Type: string;

    constructor Create(APlayID, AName, AType: string);
  end;

  TPlays = class(TObjectList<TPlay>)
  public
    function GetItemByPlayId(APlayId: string): TPlay;
  end;

implementation

constructor TPlay.Create(APlayID, AName, AType: string);
begin
  inherited Create;

  PlayId := APlayID;
  Name := AName;
  &Type := AType;
end;

function TPlays.GetItemByPlayId(APlayId: string): TPlay;
begin
  Result := nil;
  for var Play in Self do
    if ( Play.PlayID.Equals(APlayId) ) then
      Exit(Play);
end;

end.
