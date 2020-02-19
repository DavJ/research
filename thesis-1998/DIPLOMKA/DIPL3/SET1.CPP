//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set1.h"
#include "const.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TImMethod *ImMethod;
//---------------------------------------------------------------------------
__fastcall TImMethod::TImMethod(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TImMethod::btn_OKClick(TObject *Sender)
{
 //akceptuj zmìny nastavení
 Method=ImMethod->RadioGroup1->ItemIndex;   //èíslo použité zobrazovací metody
 BegCond=ImMethod->RadioGroup2->ItemIndex;  //èíslo použitých poèáteèních podmínek
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TImMethod::btn_CancelClick(TObject *Sender)
{
 this->Hide(); //ignoruj zmìny nastavení
}
//---------------------------------------------------------------------------
void __fastcall TImMethod::FormShow(TObject *Sender)
{
 char ret[100]="";
 sprintf(ret," %s%d","Nx=",Nx);this->lbNx->Caption=ret;
 sprintf(ret," %s%d","Ny=",Ny);this->lbNy->Caption=ret;
 sprintf(ret," %s%d","Nz=",Nz);this->lbNz->Caption=ret;
 ImMethod->RadioGroup1->ItemIndex=Method;    //èíslo použité zobrazovací metody
 ImMethod->RadioGroup2->ItemIndex=BegCond;   //èíslo použitých poèáteèních podmínek
}
//---------------------------------------------------------------------------


