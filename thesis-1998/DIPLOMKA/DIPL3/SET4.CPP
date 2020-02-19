//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set4.h"
#include "const.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSetColors *SetColors;
//---------------------------------------------------------------------------
__fastcall TSetColors::TSetColors(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSetColors::btn_CancelClick(TObject *Sender)
{
this->Hide();	
}
//---------------------------------------------------------------------------
void __fastcall TSetColors::btn_OKClick(TObject *Sender)
{
 WORD n;
 n=N_COLORS;
 sscanf(this->edNColors->Text.c_str(),"%hu",&n);
 N_COLORS=n;
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TSetColors::FormShow(TObject *Sender)
{
 char ret[20];
 sprintf(ret,"%hu",N_COLORS);this->edNColors->Text=ret;
}
//---------------------------------------------------------------------------