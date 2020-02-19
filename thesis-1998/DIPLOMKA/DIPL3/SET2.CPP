//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set2.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TPhantom *Phantom;
//---------------------------------------------------------------------------
__fastcall TPhantom::TPhantom(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPhantom::Btn_OKClick(TObject *Sender)
{
 sscanf(this->edNx->Text.c_str(),"%hu",&TestNx);
 sscanf(this->edNy->Text.c_str(),"%hu",&TestNy);
 sscanf(this->edNz->Text.c_str(),"%hu",&TestNz);

 if (TestNx!=0) TestNx=1<<(BYTE)ceil(log(TestNx)/log(2));  else  TestNx=1;  //bere vždy vyšší mocninu 2
 if (TestNy!=0) TestNy=1<<(BYTE)ceil(log(TestNy)/log(2));  else  TestNy=1;
 if (TestNz!=0) TestNz=1<<(BYTE)ceil(log(TestNz)/log(2));  else  TestNz=1;

 sscanf(this->edT1a->Text.c_str(),"%f",&TestT1a);
 sscanf(this->edT2a->Text.c_str(),"%f",&TestT2a);
 sscanf(this->edM0a->Text.c_str(),"%f",&TestM0a);

 sscanf(this->edT1b->Text.c_str(),"%f",&TestT1b);
 sscanf(this->edT2b->Text.c_str(),"%f",&TestT2b);
 sscanf(this->edM0b->Text.c_str(),"%f",&TestM0b);


 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TPhantom::Btn_CancelClick(TObject *Sender)
{
 this->Hide();//neregistrovat zmìny nastavení
}
//---------------------------------------------------------------------------
//vypoète testovací tkáò
void __fastcall TPhantom::TestingTissue(TISSUE *Tissue)
{
 WORD i,j,k;

 #define SetA  {Tissue->M0[k][j][i]=TestM0a;Tissue->T1[k][j][i]=TestT1a;Tissue->T2[k][j][i]=TestT2a;}
 #define SetB  {Tissue->M0[k][j][i]=TestM0b;Tissue->T1[k][j][i]=TestT1b;Tissue->T2[k][j][i]=TestT2b;}

 for(k=0;k<TestNz;k++)
  for (j=0;j<TestNy;j++)
    for (i=0;i<TestNx;i++)
    {
      switch (TestType) {
        case 0:  if (((int)ceil(log(i+1)/log(2)))%2==(((int) ceil(log(j+1)/log(2)))+((int) ceil(log(k+1)/log(2))))%2)
                   SetA
                  else SetB;
                  break;
                                      }
   }

}

void __fastcall TPhantom::FormShow(TObject *Sender)
{
  char ret[100];
  sprintf(ret,"%hu",TestNx);this->edNx->Text=ret;
  sprintf(ret,"%hu",TestNy);this->edNy->Text=ret;
  sprintf(ret,"%hu",TestNz);this->edNz->Text=ret;

  sprintf(ret,"%f",TestT1a);this->edT1a->Text=ret;
  sprintf(ret,"%f",TestT2a);this->edT2a->Text=ret;
  sprintf(ret,"%f",TestM0a);this->edM0a->Text=ret;

  sprintf(ret,"%f",TestT1b);this->edT1b->Text=ret;
  sprintf(ret,"%f",TestT2b);this->edT2b->Text=ret;
  sprintf(ret,"%f",TestM0b);this->edM0b->Text=ret;

}
//---------------------------------------------------------------------------
