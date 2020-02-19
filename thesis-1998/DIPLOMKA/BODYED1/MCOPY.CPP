//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "mcopy.h"
#include "Const_BE.cpp"
#include "undo.cpp"
#include <stdlib.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
Tfm_MCopy *fm_MCopy;
//---------------------------------------------------------------------------
__fastcall Tfm_MCopy::Tfm_MCopy(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfm_MCopy::btn_OKClick(TObject *Sender)
{
 sscanf(this->edFrom->Text.c_str(),"%hu",&from);
 sscanf(this->edTo->Text.c_str(),"%hu",&to);
 sscanf(this->edDest->Text.c_str(),"%hu",&dest);

 this->MCopy();
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_MCopy::btn_CancelClick(TObject *Sender)
{
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_MCopy::FormShow(TObject *Sender)
{
 char ret[20];
 sprintf(ret,"%hu",from);this->edFrom->Text=ret;
 sprintf(ret,"%hu",to);this->edTo->Text=ret;
 sprintf(ret,"%hu",dest);this->edDest->Text=ret;
}
//---------------------------------------------------------------------------
BYTE __fastcall Tfm_MCopy::MCopy()
{
 int i,j,k;
 WORD p;
 EXCISION  excis;
 if (to<from) {p=to;to=from;from=p;};//správné poøadí mezí
 if ((from<0)||(from>Nz-1)) return false;
 if ((to<0)||(to>Nz-1)) return false;
 if ((dest<0)||(dest>Nz-1-(to-from))) return false;   //špatné meze

 AllocExcision(0,0,dest,Nx,Ny,dest+to-from,&excis);
 if  (from<dest){//sestupné kopírování aby nedošlo k pøepsání
                 for (k=to;k>=from;k--)
   		   {
                    for(i=0;i<Nx;i++)
                      for(j=0;j<Ny;j++) {
                       //zálohování místa urèení
                       excis.Body[k-from][j][i]=aBody[k-from+dest][j][i];
                       excis.Temp[k-from][j][i]=aTemp[k-from+dest][j][i];
                       //kopírování na místo urèení
		       aBody[k-from+dest][j][i]=aBody[k][j][i];
		       aTemp[k-from+dest][j][i]=aTemp[k][j][i];
					}
   		   }
                }
 else {   //vzestupné kopírování aby nedošlo k pøepsání
                 for (k=from;k>=to;k++)
   		   {
                    for(i=0;i<Nx;i++)
                      for(j=0;j<Ny;j++) {
                       excis.Body[k-from][j][i]=aBody[k-from+dest][j][i];
                       excis.Temp[k-from][j][i]=aTemp[k-from+dest][j][i];
		       aBody[k-from+dest][j][i]=aBody[k][j][i];
		       aTemp[k-from+dest][j][i]=aTemp[k][j][i];
					}
   		   }
      }
  AddBackStep(excis);
  return true;  //kopírování probìhlo úspìšnì
}
