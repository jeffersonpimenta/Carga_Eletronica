unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, TAGraph, TASeries, TATransformations, Forms,
  Controls, Graphics, Dialogs, StdCtrls, Spin, ExtCtrls, ComCtrls, Menus,
  ActnList, Grids, uEKnob, uEMultiTurn, uESelector, ueled, RackCtls, LazSerial,
  SdpoSerial, Unit2, Unit3, Unit4, Unit5;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Chart1: TChart;
    Chart1LineSeries1: TLineSeries;
    Chart1LineSeries2: TLineSeries;
    ChartAxisTransformations1: TChartAxisTransformations;
    ChartAxisTransformations1AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    ChartAxisTransformations2: TChartAxisTransformations;
    ChartAxisTransformations2AutoScaleAxisTransform1: TAutoScaleAxisTransform;
    FloatSpinEdit1: TFloatSpinEdit;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    GroupBox3: TGroupBox;
    GroupBox4: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    LEDButton1: TLEDButton;
    LEDDisplay1: TLEDDisplay;
    LEDDisplay2: TLEDDisplay;
    MainMenu1: TMainMenu;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    MenuItem5: TMenuItem;
    MenuItem6: TMenuItem;
    MenuItem7: TMenuItem;
    OpenDialog1: TOpenDialog;
    Timer1: TTimer;
    uEKnob1: TuEKnob;
    procedure Button1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure FloatSpinEdit1Change(Sender: TObject);
    procedure FormClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure GroupBox1Click(Sender: TObject);
    procedure Label1Click(Sender: TObject);
    procedure Label2Click(Sender: TObject);
    procedure LEDButton1Click(Sender: TObject);
    procedure MenuItem2Click(Sender: TObject);
    procedure MenuItem3Click(Sender: TObject);
    procedure MenuItem4Click(Sender: TObject);
    procedure MenuItem5Click(Sender: TObject);
    procedure MenuItem6Click(Sender: TObject);
    procedure MenuItem7Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure ToggleBox1Change(Sender: TObject);
    procedure uEKnob1Change(Sender: TObject);

  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  n:integer;//variáveis que não podem ser destruídas com o final do procedure
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Label1Click(Sender: TObject);
begin

end;

procedure TForm1.Label2Click(Sender: TObject);
begin

end;

procedure TForm1.LEDButton1Click(Sender: TObject);
begin
    if timer1.Enabled then                   //função que habilita e desabilita o timer que alimenta os gráficos
     begin
      timer1.Enabled:=false;
     end
     else
     begin
      timer1.Enabled:=true;
     end;
end;

procedure TForm1.MenuItem2Click(Sender: TObject);
begin
  ShowMessage('Software para controle de carga eletrônica, veja mais em xxxx');
end;

procedure TForm1.MenuItem3Click(Sender: TObject);
begin
   Form2.Show;     //mostra tela do form2, comunicação
end;

procedure TForm1.MenuItem4Click(Sender: TObject);
begin

end;

procedure TForm1.MenuItem5Click(Sender: TObject);
begin
  Form3.show;     //mostra tela do form3
end;

procedure TForm1.MenuItem6Click(Sender: TObject);
begin
  if OpenDialog1.Execute then
     begin
       Form4.StringGrid1.LoadFromCSVFile(OpenDialog1.FileName,',',true);
       form4.Show;
      end;
end;

procedure TForm1.MenuItem7Click(Sender: TObject);
begin
  form5.Show;
end;



procedure TForm1.Timer1Timer(Sender: TObject);
begin
   n:=n+1;                                        //incrementa o marcador de coordenadas, deve ser mudado quando integrado ao hardware
  Chart1LineSeries1.AddXY(n,uEKnob1.Position);    //adiciona ao grafico
  Chart1LineSeries2.AddXY(n,1/10+uEKnob1.Position/10); //adiciona ao gráfico com um pequeno offset pra diferenciar
end;

procedure TForm1.ToggleBox1Change(Sender: TObject);
begin
  if timer1.Enabled and form2.LazSerial1.Active then                   //função que habilita e desabilita o timer que alimenta os gráficos
     begin
      timer1.Enabled:=false;
     end
     else
     begin
      timer1.Enabled:=true;
     end;
end;

procedure TForm1.uEKnob1Change(Sender: TObject);
begin
  LEDDisplay1.Value:=uEKnob1.Position;
  FloatSpinEdit1.Value:=uEKnob1.Position;       //associa o knob ao elemento abaixo dele
end;

procedure TForm1.FloatSpinEdit1Change(Sender: TObject);
begin
   uEKnob1.Position:=FloatSpinEdit1.Value;       //associa o knob ao elemento abaixo dele
end;

procedure TForm1.FormClick(Sender: TObject);
begin

end;

procedure TForm1.Button1Click(Sender: TObject);
begin
     Timer1.Enabled:=false;    //para o timer
     Chart1LineSeries1.Clear;
     Chart1LineSeries2.Clear;  //limpa as series
     n:=0;                     //zera o contador
     //Timer1.Enabled:=true;     //retoma o timer
end;

procedure TForm1.ComboBox1Change(Sender: TObject);
begin

end;

procedure TForm1.FormCreate(Sender: TObject);
begin

end;

procedure TForm1.GroupBox1Click(Sender: TObject);
begin

end;

end.

