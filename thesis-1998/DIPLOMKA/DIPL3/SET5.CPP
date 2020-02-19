//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//#include "ImProcess.cpp"
#include "imaging.h"
#include "const.cpp"
#include "set5.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
THist *Hist;
//---------------------------------------------------------------------------
__fastcall THist::THist(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THist::RadioGroup1Click(TObject *Sender)
{
  if (RadioGroup1->ItemIndex==0) {lbA->Visible=false;edA->Visible=false;}//lineární pøev.ch
  else {lbA->Visible=true;edA->Visible=true;};//logaritmická pøev.ch
}
//---------------------------------------------------------------------------
void __fastcall THist::btn_OKClick(TObject *Sender)
{
 float OldHistLog=HistLog;
 HistType=RadioGroup1->ItemIndex;   //typ. pøevodní charakteristiky
 sscanf(this->edA->Text.c_str(),"%f",&HistLog); //základ logaritmické pøevodní charakteristiky
 if ((HistLog<=0)||(HistLog==1)) {HistLog=OldHistLog;}; //akceptovat jen smysluplný základ logaritmu
 this->Hide();
 MainForm->RefreshImage(MainForm->Image,ActiveView);
 MainForm->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall THist::btn_CancelClick(TObject *Sender)
{
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall THist::FormShow(TObject *Sender)
{
 char ret[100];
 RadioGroup1->ItemIndex=HistType;   //typ. pøevodní charakteristiky

 sprintf(ret,"%f",HistLog);this->edA->Text=ret;
 RadioGroup1Click(Sender);	    //simulace kliku myši na pøepínaè	
}
//---------------------------------------------------------------------------
