//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "phase.h"
#include "const.cpp"
#include "imaging.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TRefPhase *RefPhase;
//---------------------------------------------------------------------------
__fastcall TRefPhase::TRefPhase(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRefPhase::FormShow(TObject *Sender)
{
 char ret[20];
 sprintf(ret,"%f",phase1);this->edPhase1->Text=ret;
 sprintf(ret,"%f",phase2);this->edPhase2->Text=ret;
}
//---------------------------------------------------------------------------
void __fastcall TRefPhase::BitBtn1Click(TObject *Sender)
{

 sscanf(this->edPhase1->Text.c_str(),"%f",&phase1);
 sscanf(this->edPhase2->Text.c_str(),"%f",&phase2);
 this->Hide();
 MainForm->RefreshImage(MainForm->Image,ActiveView);
 MainForm->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall TRefPhase::btn_CancelClick(TObject *Sender)
{
 this->Hide();
}
//---------------------------------------------------------------------------