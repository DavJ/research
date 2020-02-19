//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set1_BE.h"
#include "Const_BE.cpp"
#include "editor_BE.h"
//#include "editor_BE.cpp"
//#include "ImProc_BE.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TForm4::BitBtn1Click(TObject *Sender)
{
 float f;
 sscanf(this->edB0->Text.c_str(),"%f",&f);
 B0=f;

 sscanf(this->edTemp->Text.c_str(),"%f",&f);
 Temp=f;
 Form1->ReadLUT();  //nové naètení vyhledávací tabulky z pøepoèítané db.tabulky
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::BitBtn2Click(TObject *Sender)
{
  char ret[100]="";
  sprintf(ret," %f",B0);Form4->edB0->Text=ret;
  sprintf(ret," %f",Temp);Form4->edTemp->Text=ret;

  this->Hide(); //ignoruj zmìny nastavení
}
//---------------------------------------------------------------------------
void __fastcall TForm4::edB0Change(TObject *Sender)
{
 float f;
 char ret[100]="";
 sscanf(this->edB0->Text.c_str(),"%f",&f);
 Freq=GamaH*f/(2*Pi);
 sprintf(ret," %f",1e-6*Freq);
 lbFreq->Caption=ret;
}
//---------------------------------------------------------------------------

