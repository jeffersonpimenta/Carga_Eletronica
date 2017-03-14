unit Unit4;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, TAGraph, TASeries, TATransformations,
  TAIntervalSources, Forms, Controls, Graphics, Dialogs, Grids, StdCtrls;

type

  { TForm4 }

  TForm4 = class(TForm)
    Chart1: TChart;
    Chart1LineSeries1: TLineSeries;
    Chart1LineSeries2: TLineSeries;
    ChartAxisTransformations1: TChartAxisTransformations;
    ChartAxisTransformations1AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    ChartAxisTransformations2: TChartAxisTransformations;
    ChartAxisTransformations2AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    StringGrid1: TStringGrid;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form4: TForm4;

implementation

{$R *.lfm}

{ TForm4 }

procedure TForm4.FormShow(Sender: TObject);
var
j: integer;
begin



  for j:=0 to StringGrid1.RowCount-1 do
  begin
            Chart1LineSeries1.AddXY(StrToInt(StringGrid1.Cells[0,j]),StrToFloat(StringReplace(StringGrid1.Cells[1,j],'.',',',[rfReplaceAll, rfIgnoreCase])));
            Chart1LineSeries2.AddXY(StrToInt(StringGrid1.Cells[0,j]),(1/10+StrToFloat(StringReplace(StringGrid1.Cells[2,j],'.',',',[rfReplaceAll, rfIgnoreCase]))));  //adiciona ao gráfico e toma o cuidado de voltar o . para ,
  end;


end;

procedure TForm4.FormCreate(Sender: TObject);
begin

end;

end.

