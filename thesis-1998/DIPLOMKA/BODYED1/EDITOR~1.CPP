//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "editor_BE.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ImProc_BE.cpp"
#include "set1_BE.cpp"
#include "set2_BE.cpp"
#include "Const_BE.cpp"
#include "io_data.cpp"
#include "mcopy.cpp"
#include "temp.cpp"
#include "conf_BE.cpp"  

#include "tool.cpp"
#include "status.cpp"
#include "about_BE.cpp"
#include "set4_BE.cpp"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
  WORD  i,j,k;

  //nastavení vyhledávací tabulky podle databáze
  ReadLUT();
  //ukazatel na ScrollBar bude v promìnné slider
  Slider=ScrollBar1;
  // inicializace palety a obrazu
  plTissues=AllocLgPl(NRecords);
  hpalTissues=TissueColors(plTissues);//alokace a výpoèet palety pro zobrazení tkání


  hpalShades=Shades(N_SHADES);   //alokace a výpoèet palety pro zobrazení rozložení teploty

  InitColor(); //inicializace barevného indikátoru vybrané tkánì

  //není-li nakonfigurováno jinak -tkáò pozadí 0-tá tkáò z vyhled. tabulky
  sprintf(BcgTissName,"%s",LookUp[0].tissue);
  LoadConfiguration(); //ètení konfigurace ze systémového registru
  BcgTissue=GetIndex(BcgTissName);

  aBody=ByteAlloc_3D(Nz,Ny,Nx);     //alokace nových polí
  aTemp=FloatAlloc_3D(Nz,Ny,Nx);
  aView=ByteAlloc_2D(Ny,Nx);

  for (i=0;i<Nx;i++)
    for (j=0;j<Ny;j++)
      for (k=0;k<Nz;k++)
        {
         aBody[k][j][i]=BcgTissue;
         aTemp[k][j][i]=Temp;
        }
  Slider->Min=0;
  Slider->Max=Nz-1;
  PosX=0;PosY=0;PosZ=0; //nastavení nové pozice v tìlese
  Slider->Position=0;  //nastavení pozice slideru
  if (Nz==1) Slider->Visible=false; else Slider->Visible=true; //zakáže scroll-bar u 2D tìlesa
  RefreshLabels();
  RefreshImage(Image,ActiveView);
}
//-----------------------nastavení vyhledávací tabulky podle databáze---------------------------------------------
void __fastcall TForm1::ReadLUT()
{
  NRecords=GetNRecords(Table1);      //zjistí poèet záznamù v databázi
  SetLUTable(Table1,Table1TKAN,Table1T1,Table1T2,Table1NPROT,Table1KT1,Table1KT2,Table1RED,Table1GREEN,Table1BLUE );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowStatus(char *ret)
{
 fm_Status->Label1->Caption=ret;
 fm_Status->Show();
 Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshLabels()
{
  char ret[100];
  float T1,T2,M0;

  sprintf(ret,"%3d%c%3d%c%3d",PosX,':',PosY,':',PosZ);this->lbPosition->Caption=ret;
  CountNMRParams(aBody[PosZ][PosY][PosX],aTemp[PosZ][PosY][PosX],&T1,&T2,&M0);
  sprintf(ret,"%s",LookUp[aBody[PosZ][PosY][PosX]].tissue);this->lbTissue->Caption=ret;
  sprintf(ret,"%f",T1);this->lbT1->Caption=ret;
  sprintf(ret,"%f",T2);this->lbT2->Caption=ret;
  sprintf(ret,"%f",M0);this->lbM0->Caption=ret;
  sprintf(ret,"%f",aTemp[PosZ][PosY][PosX]);this->lbTemp->Caption=ret;
}

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
  FILE *outfile;
  char buff[100];
  sprintf(buff,"Uložení tkánì");
  SaveDialog1->Title=buff;
  if (SaveDialog1->Execute())
    {
     outfile=fopen(SaveDialog1->FileName.c_str(),"wt");
     if (outfile) fprintf(outfile,"Editor tkání");
     for (int i=0;i<DBGrid1->FieldCount;i++)
       fprintf(outfile,"%s %s\n",
               DBGrid1->Fields[i]->FieldName.c_str(),
               DBGrid1->Fields[i]->AsString.c_str());

     fclose(outfile);
    }
}

int IsNumber(char *ret)
{
  return sscanf(ret,"%f");
}

void __fastcall TForm1::InitColor()
{
Color->Picture->Bitmap->Palette=hpalTissues;
hbmp=CreateBitmap(1,1,1, 8,aPalette[0]);
Color->Picture->Bitmap->Handle =hbmp;
if (Color->Picture->Bitmap->Handle == NULL) MessageBox(NULL,"Nepodaøilo  se vytvoøit bitmapu !","message",MB_OK);
Application->ProcessMessages();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::Table1CalcFields(TDataSet *DataSet)
{
 char ret[100]="";
 int n;

 //výpoèet frekvenèní závislosti T1
 sprintf(ret,"%f",Table1A->AsFloat*exp(Table1B->AsFloat*log(Freq)));
 Table1T1->Value=ret;

  //zmìna aktuální tkánì
  sprintf(ret,"%s",Table1TKAN->AsString.c_str());
  ActTissue=GetIndex(ret);

  //zmìna barvy v indikaèním okénku
  Color->Canvas->Pixels[0][0]=PALETTERGB(Table1RED->AsInteger,Table1GREEN->AsInteger,Table1BLUE->AsInteger);
 }
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
 ByteDealloc_2D(aView);
 ByteDealloc_3D(aBody,Nz);
 FloatDealloc_3D(aTemp,Nz);

 SaveConfiguration();  //zápis konfigurace do systémového registru
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ImageMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    PosX=floor(((Nx-0.001)*X)/Image->Width);
    PosY=floor(((Ny-0.001)*Y)/Image->Height);
    this->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageClick(TObject *Sender)
{
 switch (fm_Tool->ActiveTool) {
          case atlPoi:    DrawPoint(); break;
          case atlSph:    DrawSphere(); break;
          case atlEll:    DrawEllipsoid();break;
 	  case atlRec:    DrawRectangular();break;
 	  case atlCub:    DrawCube();break;
 	  case atlCyl:    DrawCylinder();break;
                     }

    RefreshImage(Image,ActiveView);
  }

//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{

 ScrollBar1->Enabled=false; //zakáže reakce na myš
 PosZ=ScrollBar1->Position;
 //pøekreslení obrázku
 RefreshImage(Image,ActiveView);
 ScrollBar1->Enabled=true; //povolí reakce na myš
 this->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Fyziklnparametry1Click(TObject *Sender)
{
  char ret[100]="";
  sprintf(ret," %f",B0);Form4->edB0->Text=ret;
  sprintf(ret," %f",Temp);Form4->edTemp->Text=ret;

  Form4->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Zobrazen1Click(TObject *Sender)
{
 Form5->Show();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Uloit1Click(TObject *Sender)
{
 FILE *outfile;
 char buff[255];
 sprintf(buff,"Uložení souboru");
 SaveDialog1->Title=buff;
 //v Object Inspectoru jsou nastaveny filtry *.*,*.bod,*.nmr
 //jako aktivní je nastaven filtr *.bod (položka IndexFiltr)

 /*pro zabránìní pøepsání již existujícího souboru je nastaveno
   Options  ofOverwritePrompt na true; */

 if (SaveDialog1->Execute())
 {
    outfile=fopen(SaveDialog1->FileName.c_str(),"wb");

    if (outfile!=NULL)
      {
       ShowStatus(savemsg);
       //rozlišení zda se jedná o uložení souboru *.bod ,*.nmr
       if (strstr(strlwr(SaveDialog1->FileName.c_str()),".nmr")!=NULL) savenmr(outfile);
       if (strstr(strlwr(SaveDialog1->FileName.c_str()),".bod")!=NULL) savebod(outfile);
       fm_Status->Hide();
      }

    fclose(outfile);

 }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Tissue1Click(TObject *Sender)
{
 btn_Tissue->Down=true;btn_Temp->Down=false;
 Image->Picture->Bitmap->Palette=TissueColors(plTissues/*,Table1,Table1TKAN,Table1RED,Table1GREEN,Table1BLUE**/);
 RefreshImage(Image,actTis);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Temperature1Click(TObject *Sender)
{
 btn_Tissue->Down=false;btn_Temp->Down=true;
 Image->Picture->Bitmap->Palette=Shades(N_SHADES);
 RefreshImage(Image,actTem);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Paletu1Click(TObject *Sender)
{
  for (WORD i=0;i<256;i++) {aPalette[i][0]=i;aPalette[i][1]=i;}
  RefreshImage(Image,actPal);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_undoClick(TObject *Sender)
{
  Undo();
  RefreshImage(Image,ActiveView);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_pointClick(TObject *Sender)
{
    fm_Tool->ActiveTool=atlPoi;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_sphereClick(TObject *Sender)
{
 fm_Tool->ActiveTool=atlSph;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_sphereMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
   if (Button==mbRight) fm_Tool->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tl_ellipticalClick(TObject *Sender)
{
  fm_Tool->ActiveTool=atlEll;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_rectangularClick(TObject *Sender)
{
  fm_Tool->ActiveTool=atlRec;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_cubeClick(TObject *Sender)
{
 fm_Tool->ActiveTool=atlCub;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tl_cylinderClick(TObject *Sender)
{
 fm_Tool->ActiveTool=atlCyl;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_CopyClick(TObject *Sender)
{
 fm_MCopy->from=PosZ; fm_MCopy->to=PosZ;fm_MCopy->dest=PosZ;
 fm_MCopy->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_tClick(TObject *Sender)
{
 fm_Temp->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_TempClick(TObject *Sender)
{
 Temperature1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_TissueClick(TObject *Sender)
{
 Tissue1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Konec1Click(TObject *Sender)
{
   Application->Terminate(); //vyvolá PostQuitMessage
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Novtk1Click(TObject *Sender)
{
 WORD  i,j,k;
 if (IDOK&Application->MessageBox("Všechna data budou ztracena","Výstraha",MB_OKCANCEL))
  {
   ClearUndo( NBackSteps);            //vymazání všech zpìtných krokù z pamìti

   for (i=0;i<Nx;i++)                //vymazání tìlesa
     for (j=0;j<Ny;j++)
       for (k=0;k<Nz;k++)
         {
          aBody[k][j][i]=BcgTissue;
          aTemp[k][j][i]=Temp;
         }
    RefreshImage(Image,ActiveView);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Otevt1Click(TObject *Sender)
{
 FILE *infile;
 char buff[255];
 sprintf(buff,"Otevøení souboru");
 SaveDialog1->Title=buff;
 //v Object Inspectoru jsou nastaveny filtry *.*,*.bod,*.nmr
 //jako aktivní je nastaven filtr *.bod (položka IndexFiltr)

 /*pro zabránìní pøepsání již existujícího souboru je nastaveno
   Options  ofOverwritePrompt na true; */
 if (OpenDialog1->Execute())
 {
    infile=fopen(OpenDialog1->FileName.c_str(),"rb");
    if (infile!=NULL)
      {
       ShowStatus(openmsg);
       ClearUndo(NBackSteps);            //vymazání všech zpìtných krokù z pamìti
       ByteDealloc_2D(aView);		 //dealokace starých polí
       ByteDealloc_3D(aBody,Nz);
       FloatDealloc_3D(aTemp,Nz);
       loadbod(infile);                  //nahrátí souboru pole
       RefreshImage(Image,ActiveView);
       fm_Status->Hide();
      }

    fclose(infile);
 }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::Info1Click(TObject *Sender)
{
  fm_About->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Npovda1Click(TObject *Sender)
{
  Application->HelpJump("_obsah");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Barvy1Click(TObject *Sender)
{
 SetColors->Show();
}
//---------------------------------------------------------------------------
