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
 //akceptuj zm�ny nastaven�
 Method=ImMethod->RadioGroup1->ItemIndex;   //��slo pou�it� zobrazovac� metody
 BegCond=ImMethod->RadioGroup2->ItemIndex;  //��slo pou�it�ch po��te�n�ch podm�nek
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TImMethod::btn_CancelClick(TObject *Sender)
{
 this->Hide(); //ignoruj zm�ny nastaven�
}
//---------------------------------------------------------------------------
void __fastcall TImMethod::FormShow(TObject *Sender)
{
 char ret[100]="";
 sprintf(ret," %s%d","Nx=",Nx);this->lbNx->Caption=ret;
 sprintf(ret," %s%d","Ny=",Ny);this->lbNy->Caption=ret;
 sprintf(ret," %s%d","Nz=",Nz);this->lbNz->Caption=ret;
 ImMethod->RadioGroup1->ItemIndex=Method;    //��slo pou�it� zobrazovac� metody
 ImMethod->RadioGroup2->ItemIndex=BegCond;   //��slo pou�it�ch po��te�n�ch podm�nek
}
//---------------------------------------------------------------------------


