unit Unit3;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, TAGraph, TASeries, TATransformations, Forms,
  Controls, Graphics, Dialogs, StdCtrls, Spin, Grids, ExtDlgs, ExtCtrls, Unit2;

type

  { TForm3 }

  TForm3 = class(TForm)
    Button1: TButton;
    Chart1: TChart;
    Chart1LineSeries1: TLineSeries;
    Chart1LineSeries2: TLineSeries;
    ChartAxisTransformations1: TChartAxisTransformations;
    ChartAxisTransformations1AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    ChartAxisTransformations2: TChartAxisTransformations;
    ChartAxisTransformations2AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    FloatSpinEdit1: TFloatSpinEdit;
    FloatSpinEdit2: TFloatSpinEdit;
    GroupBox1: TGroupBox;
    Energia: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    SaveDialog1: TSaveDialog;
    Timer1: TTimer;
    ToggleBox1: TToggleBox;
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure ToggleBox1Change(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form3: TForm3;
   o: integer;
implementation

{$R *.lfm}

{ TForm3 }

procedure TForm3.Button1Click(Sender: TObject);
var
arq: TextFile;
aux,aux1: string;
i: integer;
begin

  if SaveDialog1.Execute then
  begin

    AssignFile(arq,SaveDialog1.FileName);    //assimila arq ao caminho
    Rewrite(arq);                            //habilita gravação

    For i := 0 to (round(Chart1LineSeries1.MaxXValue)-1) do  //idenfifica cada linha do gráfico e adiciona no arquivo
    begin

         aux:=StringReplace(FloatToStr(Chart1LineSeries1.GetYValue(i)),',','.',[rfReplaceAll, rfIgnoreCase]);     //troca , por . no número
         aux1:=StringReplace(FloatToStr(Chart1LineSeries2.GetYValue(i)),',','.',[rfReplaceAll, rfIgnoreCase]);     //troca , por . no número
         Writeln(arq,i,',',aux,',',aux1);             //escreve no arquivo

    end;

    CloseFile(arq);  //fecha arquivo

  end;



end;

procedure TForm3.Timer1Timer(Sender: TObject);
begin

  Chart1LineSeries1.AddXY(o,o);    //adiciona ao grafico
  Chart1LineSeries2.AddXY(o,o/10);
  o:=o+1;                         //incrementa contador
end;

procedure TForm3.ToggleBox1Change(Sender: TObject);
begin
  if form2.LazSerial1.Active then
  begin

  end
  else
  begin
       ShowMessage('Conecte o equipamento antes de iniciar a medição');
  end;
end;

end.

