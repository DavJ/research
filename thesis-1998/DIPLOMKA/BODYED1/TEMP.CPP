//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "temp.h"
#include "Const_BE.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

Tfm_Temp *fm_Temp;
//---------------------------------------------------------------------------
__fastcall Tfm_Temp::Tfm_Temp(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Temp::btn_OKClick(TObject *Sender)
{
   sscanf(this->edTemp->Text.c_str(),"%f",&ActTemp);
   this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Temp::btn_CancelClick(TObject *Sender)
{
   this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Temp::FormShow(TObject *Sender)
{
 char ret[20];
 sprintf(ret,"%f",ActTemp);this->edTemp->Text=ret;
}
//---------------------------------------------------------------------------
