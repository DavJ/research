

#include <vcl\vcl.h>
#pragma hdrstop

/*doplnene  include*/
#include "imaging.h"
#include "ImProcess.cpp"
#include "set1.cpp"
#include "set2.cpp"
#include "set3.cpp"
#include "set4.cpp"
#include "set5.cpp"
#include "conf.cpp"
#include "matrix_io.cpp"
#include "About.cpp"
#include "phase.cpp"

#include <math.h>

//---------------------------------------------------------------------------
#pragma link "ChartFX"
#pragma resource "*.dfm"
TMainForm *MainForm;


//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{

}
//------------------------------aktualizace zobrazení návìští----------------------------------
void __fastcall TMainForm::RefreshLabels()
{
  char ret[100];
  sprintf(ret,"%3d%c%3d%c%3d",PosX,':',PosY,':',PosZ);this->lbPos->Caption=ret;

  switch (ActiveView) {
    case actM0: sprintf(ret,"%f",Tissue.M0[PosZ][PosY][PosX]);break;
    case actT1: sprintf(ret,"%f",Tissue.T1[PosZ][PosY][PosX]);break;
    case actT2: sprintf(ret,"%f",Tissue.T2[PosZ][PosY][PosX]);break;
    case actMx:
    case actMy: sprintf(ret,"%f \n%f ",real(aCplxEnvelope[PosZ][PosY][PosX]),imag(aCplxEnvelope[PosZ][PosY][PosX]));break;
    case actReal:
    case actImag: sprintf(ret,"%f \n%f ",real(aCplxImage[PosZ][PosY][PosX]),imag(aCplxImage[PosZ][PosY][PosX]));break;
                     }
   this->lbValue->Caption=ret;

  sprintf(ret,"%f",HistMin);this->lbMin->Caption=ret;
  sprintf(ret,"%f",HistMax);this->lbMax->Caption=ret;


if (HistType==0) {this->lbHist->Caption="Lin";}    //lineární pøev.ch
             else  {this->lbHist->Caption="Log";}; //logaritmická pøev.ch

}
//--------------------------------aktualizace zobrazení obrazu--------------------------------------
void __fastcall TMainForm::RefreshImage(TImage *Image,BYTE active)
{
  ActiveView=active;
  switch (ActiveView) {
    case actM0: PutToImage(aImage,Tissue.M0[PosZ],Ny,Nx);break;
    case actT1: PutToImage(aImage,Tissue.T1[PosZ],Ny,Nx);break;
    case actT2: PutToImage(aImage,Tissue.T2[PosZ],Ny,Nx);break;
    case actMx: Real_2D(aImage,aCplxEnvelope[PosZ],Ny,Nx,phase1);break;
    case actMy: Imag_2D(aImage,aCplxEnvelope[PosZ],Ny,Nx,phase1);break;
    case actReal: Real_2D(aImage,aCplxImage[PosZ],Ny,Nx,phase2);break;
    case actImag: Imag_2D(aImage,aCplxImage[PosZ],Ny,Nx,phase2);break;

  }

  if (!ActiveView==actNO)Histogram(aImage,aView,Ny,Nx);  //úprava histogramu

  hbmp=CreateBitmap(Nx,Ny, 1, 8,aView[0]);//musí být po každé zmìnì pole aView jinak se nevykreslí
  Image->Picture->Bitmap->Handle =hbmp;

  if (Image->Picture->Bitmap->Handle == NULL) MessageBox(NULL,"Nepodaøilo  se vytvoøit bitmapu !","message",MB_OK);
  Application->ProcessMessages();
}



//---------------------------------------------------------------------------
   void __fastcall TMainForm::ShowMessage(BYTE msg)
{
   switch (msg) {
      case msgTis:MessageBox(NULL,"Není otevøena žádná tkáò.","Zpráva",MB_OK);break;
      case msgSig:MessageBox(NULL,"Není vypoèítán signál.","Zpráva",MB_OK);break;
      case msgBmp:MessageBox(NULL,"Nepodaøilo se vytvoøit bitmapu.","Zpráva",MB_OK);break;
      case msgNoCpl:MessageBox(NULL,"Aktuálnì zobrazená data nelze uložit  ve formátu *.cpl .","Zpráva",MB_OK);break;
      case msgBreak:MessageBox(NULL,"Výpoèet pøerušen uživatelem","Zpráva",MB_OK);break;
      default : MessageBox(NULL,"Neznámá zpráva.","Zpráva",MB_OK);break;
   		}
}
//---------------------------------------------------------------------------
   void __fastcall TMainForm::EnableTissButtons()
{
   this->btn_M0->Enabled=true;
   this->btn_T1->Enabled=true;
   this->btn_T2->Enabled=true;
}

   void __fastcall TMainForm::EnableAllButtons()
{
   this->btn_M0->Enabled=true;
   this->btn_T1->Enabled=true;
   this->btn_T2->Enabled=true;

   this->btn_Mx->Enabled=true;
   this->btn_My->Enabled=true;

   this->btn_Re->Enabled=true;
   this->btn_Im->Enabled=true;
}

//---------------------------------------------------------------------------
   void __fastcall TMainForm::DisableAllButtons()
{
   this->btn_M0->Enabled=false;
   this->btn_T1->Enabled=false;
   this->btn_T2->Enabled=false;

   this->btn_Mx->Enabled=false;
   this->btn_My->Enabled=false;

   this->btn_Re->Enabled=false;
   this->btn_Im->Enabled=false;
}

   void __fastcall TMainForm::DisableTissButtons()
{
   this->btn_M0->Enabled=false;
   this->btn_T1->Enabled=false;
   this->btn_T2->Enabled=false;
}

//--------------inicializace programu -----------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
//SetField();
  SetField1();          //výpoèet default hodnot magnetického pole
  LoadConfiguration();  //nahrátí konfigurace
  OldMethod=Method;OldBegCond=BegCond; //inicializace stavu programu

  // inicializace palety a obrazu
  Image->Picture->Bitmap->Palette=Shades(N_SHADES);
}

//--------------------------------------------------------------------------- ukonèení aplikace------------------------------------------
void __fastcall TMainForm::Konec1Click(TObject *Sender)
{
  Application->Terminate(); //vyvolá PostQuitMessage
}

//--------------vykreslení aktivni palety barev ----------------------------------------------
void __fastcall TMainForm::Paletu1Click(TObject *Sender)
{
  WORD i;
  if (!counted[n_pale])
    {
      for (i=0;i<256;i++) {aPalette[i][0]=i;aPalette[i][1]=i;}
      counted[n_pale]=1;
    }
  hbmppal=  CreateBitmap(2,256, 1, 8,aPalette[0]);//musí být po každé zmìnì pole a Palette jinak nefunguje
  Image->Picture->Bitmap->Handle = hbmppal;
  if (Image->Picture->Bitmap->Handle == NULL) ShowMessage(msgBmp);//nepodaøilo se vytvoøit bitmapu

  Image->Refresh();Application->ProcessMessages();

 }
//---------------------------------------------------------------------------
void __fastcall TMainForm::M01Click(TObject *Sender)
{
if (!this->btn_M0->Down) this->btn_M0->Down=true;
DisableAllButtons();
if (counted[n_tkan])
  {
  RefreshImage(Image,actM0);
  this->RefreshLabels();
  }
  else ShowMessage(msgTis);//ZPRÁVA:není otevøena tkáò
EnableAllButtons();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Mx1Click(TObject *Sender)
{
  if (!this->btn_Mx->Down) this->btn_Mx->Down=true;
  if (!counted[n_tkan]) {ShowMessage(msgTis);return;};//ZPRÁVA : není otevøena tkáñ
  DisableAllButtons();

  if (!counted[n_sign]||(Method!=OldMethod)||(BegCond!=OldBegCond))
    {
    switch (Method){
      case met33D :   GetSignal33D(ImMethod->RadioGroup2->ItemIndex);break;
      case met32D :   GetSignal32D(ImMethod->RadioGroup2->ItemIndex);break;

                  }

     counted[n_sign]=1;counted[n_reko]=0;
     OldMethod=Method; OldBegCond=BegCond;
    }
    RefreshImage(Image,actMx);
    this->RefreshLabels();
 EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::real1Click(TObject *Sender)
{
    if (!this->btn_Re->Down) this->btn_Re->Down=true;
    if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
    DisableAllButtons();

    if (!counted[n_reko])  switch (Method)
      {
       case met33D : GetImage33D(aCplxImage,aCplxEnvelope,Nz,Ny,Nx);break;
       case met32D : GetImage32D(aCplxImage,aCplxEnvelope,Nz,Ny,Nx);break;
      }
  counted[n_reko]=1;
  RefreshImage(Image,actReal);
  RefreshLabels();
  EnableAllButtons();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::imag1Click(TObject *Sender)
{
    if (!this->btn_Im->Down) this->btn_Im->Down=true;
    if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
    DisableAllButtons();
    if (!counted[n_reko])switch (Method)
       {
        case met33D : GetImage33D(aCplxImage,aCplxEnvelope,Nz,Ny,Nx);break;
        case met32D : GetImage32D(aCplxImage,aCplxEnvelope,Nz,Ny,Nx);break;
       }
  counted[n_reko]=1;
  RefreshImage(Image,actImag);
  this->RefreshLabels();
  EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Otevt1Click(TObject *Sender)
{
  FILE *infile;
  char buff[255];
  sprintf(buff,"Otevøení souboru");

  OpenDialog1->Title=buff;

  if (OpenDialog1->Execute())
 {
    infile=fopen(OpenDialog1->FileName.c_str(),"rb");
    if (infile!=NULL)
      {
       //rozlišení zda se jedná o uložení souboru *.cpl (a implicitnì vše ostatní) nebo *.nmr
       if (strstr(strlwr(OpenDialog1->FileName.c_str()),".nmr")!=NULL)
          {
           DeallocAll(Nz);
           Tissue=LoadTissue(infile);

           AllocAll(Nz,Ny,Nx);     //zde alokuje všechny promìnné kromì Tissue

           counted[n_tkan]=1;
           counted[n_sign]=0; //signál je nutno pøepoèítat
           counted[n_reko]=0; //rekonstrukci je nutno pøepoèítat
           M01Click(Sender); //zobrazení distribuce M0 -simuluje klik myší
           EnableAllButtons();
          }
       if (strstr(strlwr(OpenDialog1->FileName.c_str()),".cpl")!=NULL)
          {
/*           switch (ActiveView) {
           case actM0: case actT1: case actT2:
                       ShowMessage(msgNoCpl);
           	       break;
           case actMx:
           case actMy:*/
           DeallocAll(Nz);
           aCplxEnvelope=LoadCplx(infile);
           counted[n_tkan]=1;  //pozor! zde není vypoèítána tkáò(je pouze alokovaná)
           counted[n_sign]=1;
           counted[n_reko]=0; //rekonstrukci je nutno pøepoèítat
           DisableTissButtons();  //zakázání tlaèítek pro zobrazení tkánì

           /*break;
           case actReal:
           case actImag:DeallocAll(Nz);
                        aCplxImage=LoadCplx(infile);
                        counted[n_tkan]=false;
                        counted[n_sign]=true;//pozor! zde není vypoèítán signál
                        counted[n_reko]=true;
                        break;
                     }   */
           AllocAll(Nz,Nx,Ny);     //zde alokuje všechny promìnné kromì nahrané ze souboru
           Mx1Click(Sender);      //zobrazení distribuce Mx -simuluje klik myší
          }

         PosZ=0;
         Slider->Min=0;
         Slider->Max=Nz-1;
         Slider->Enabled=true;
      }

    fclose(infile);
 }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UlozitClick(TObject *Sender)
{
  FILE *outfile;
  char buff[255];
  sprintf(buff,"Uložení dat do souboru");

  SaveDialog1->Title=buff;

  if (SaveDialog1->Execute())
   {
    if (strstr(strlwr(SaveDialog1->FileName.c_str()),".bmp")!=NULL)
     {
     Image->Picture->SaveToFile(SaveDialog1->FileName.c_str());
     }

    if (strstr(strlwr(SaveDialog1->FileName.c_str()),".cpl")!=NULL)
     {
      outfile=fopen(SaveDialog1->FileName.c_str(),"wb");
      if (outfile!=NULL)
        {
        //uložení aktuálnì zobrazovaného pole do souboru *.cpl
         switch (ActiveView) {
        case actM0: case actT1: case actT2:
                         ShowMessage(msgNoCpl);
                         break;
        case actMx: case actMy:
                         SaveCplx(outfile,Nz,Ny,Nx,aCplxEnvelope);
                         break;
        case actReal: case actImag:
                         SaveCplx(outfile,Nz,Ny,Nx,aCplxImage);
                         break;
                             }

        }
       fclose(outfile);
     }


   }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ScrollBar1Change(TObject *Sender)
{
 //char zPos[10];
 ScrollBar1->Enabled=false; //zakáže reakce na myš
 PosZ=ScrollBar1->Position;

 RefreshImage(Image,ActiveView);  //pøekreslení obrázku
 ScrollBar1->Enabled=true; //povolí reakce na myš
 this->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImageMouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
{

    PosX=floor(((Nx-0.001)*X)/Image->Width);
    PosY=floor(((Ny-0.001)*Y)/Image->Height);
    this->RefreshLabels();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::T11Click(TObject *Sender)
{
if (!this->btn_T1->Down) this->btn_T1->Down=true;
DisableAllButtons();

if (counted[n_tkan])
  {
  RefreshImage(Image,actT1);
  this->RefreshLabels();
  }
  else ShowMessage(msgTis);//ZPRÁVA  není otevøena žádná tkáò
 EnableAllButtons();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::T21Click(TObject *Sender)
{
  if (!this->btn_T2->Down) this->btn_T2->Down=true;
  DisableAllButtons();

  if (counted[n_tkan])
    {
    RefreshImage(Image,actT2);
    this->RefreshLabels();
    }
    else ShowMessage(msgTis);//ZPRÁVA: není otevøena žádná tkáò

  EnableAllButtons();
 }

void __fastcall TMainForm::Real2Click(TObject *Sender)
{
  WORD i,j,k;

  for(k=0;k<Nz;k++)
    for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=complex(Tissue.M0[k][j][i],0);

  fft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));
  RefreshImage(Image,actReal);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Imag2Click(TObject *Sender)
{
  WORD i,j,k;

  for(k=0;k<Nz;k++)
    for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=complex(Tissue.M0[k][j][i],0);

  fft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));
  RefreshImage(Image,actImag);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Real3Click(TObject *Sender)
{

  ifft3(aCplxImage,aCplxEnvelope,order(Nz),order(Ny),order(Nx));
  RefreshImage(Image,actMx);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Imag3Click(TObject *Sender)
{
  ifft3(aCplxImage,aCplxEnvelope,order(Nz),order(Ny),order(Nx));
  RefreshImage(Image,actMy);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Real4Click(TObject *Sender)
{
  WORD i,j,k;

  for(k=0;k<Nz;k++)
    for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=complex(Tissue.M0[k][j][i],0);
  RefreshImage(Image,actMx);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Imag4Click(TObject *Sender)
{
   WORD i,j,k;

  for(k=0;k<Nz;k++)
    for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=complex(Tissue.M0[k][j][i],0);
  RefreshImage(Image,actMy);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::All1Click(TObject *Sender)
{
  WORD i,j,k;
  complex c;
  for(k=0;k<Nz;k++)
    for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=complex(Tissue.M0[k][j][i],0);

  fft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));

  for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxImage[k][j][i]=conj(aCplxImage[k][j][i]);

  fft3(aCplxImage,aCplxEnvelope,order(Nz),order(Ny),order(Nx));

  for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
        aCplxEnvelope[k][j][i]=conj(aCplxEnvelope[k][j][i])/(Nx*Ny*Nz);

  RefreshImage(Image,actMx);
}



void __fastcall TMainForm::SetShowingClick(TObject *Sender)
{
 ImMethod->Show();
}



void __fastcall TMainForm::SetTestClick(TObject *Sender)
{
 Phantom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::My1Click(TObject *Sender)
{
  if (!this->btn_My->Down) this->btn_My->Down=true;
  if (!counted[n_tkan]) {ShowMessage(msgTis);return;};//ZPRÁVA : není otevøena tkáñ
  DisableAllButtons();
  if (!counted[n_sign]||(Method!=OldMethod)||(BegCond!=OldBegCond))
    {
    switch (Method){
      case met33D :   GetSignal33D(ImMethod->RadioGroup2->ItemIndex);break;
      case met32D :   GetSignal32D(ImMethod->RadioGroup2->ItemIndex);break;
                   }


     counted[n_sign]=1;counted[n_reko]=0;
     OldMethod=Method;OldBegCond=BegCond;
    }
    RefreshImage(Image,actMy);
    this->RefreshLabels();
 EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Testovactleso1Click(TObject *Sender)
{
  DeallocAll(Nz);
  Nx=TestNx;Ny=TestNy;Nz=TestNz;
  AllocAll(Nz,Ny,Nx);
  Phantom->TestingTissue(&Tissue);

  counted[n_tkan]=1;
  counted[n_sign]=0; //signál je nutno pøepoèítat
  counted[n_reko]=0; //rekonstrukci je nutno pøepoèítat

  PosZ=0;
  Slider->Min=0;
  Slider->Max=Nz-1;
  Slider->Enabled=true;
  M01Click(Sender); //zobrazení distribuce M0 -simuluje klik myší
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetFieldClick(TObject *Sender)
{
 //Form1->Field=&Field;
 //Form1->NewField=&NewField;
 Form1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Ncolors1Click(TObject *Sender)
{
 char ret[100];
 sprintf(ret,"%hu",N_COLORS);

 SetColors->edNColors->Text=ret;
 SetColors->Show();
}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
 SaveConfiguration();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Info1Click(TObject *Sender)
{
 fm_About->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Npovda1Click(TObject *Sender)
{
   Application->HelpJump("_obsah");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Dkorekce1Click(TObject *Sender)
{
  if (!this->btn_Re->Down) this->btn_Re->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  PhaseCorect2D(aCplxImage);
  RefreshImage(Image,actReal);
  this->RefreshLabels();
  //counted[n_reko]=0;

  EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dkorekce1Click(TObject *Sender)
{
  if (!this->btn_Im->Down) this->btn_Im->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  PhaseCorect2D(aCplxImage);
  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dreal1Click(TObject *Sender)
{
  if (!this->btn_Re->Down) this->btn_Re->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  PhaseCorect3D(aCplxImage);
  RefreshImage(Image,actReal);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dimag1Click(TObject *Sender)
{
  if (!this->btn_Im->Down) this->btn_Im->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  PhaseCorect3D(aCplxImage);
  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::N2DFFT1Click(TObject *Sender)
{
 WORD m;

 if (!this->btn_Re->Down) this->btn_Re->Down=true;
 if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
 DisableAllButtons();


for (m=0;m<Nz;m++)
    fft2(aCplxEnvelope[m],aCplxImage[m],order(Ny),order(Nx));

  RefreshImage(Image,actReal);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2DIFFT1Click(TObject *Sender)
{
WORD m;

 if (!this->btn_Im->Down) this->btn_Im->Down=true;
 if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
 DisableAllButtons();


for (m=0;m<Nz;m++)
    fft2(aCplxEnvelope[m],aCplxImage[m],order(Ny),order(Nx));

  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();


}

//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dreal3Click(TObject *Sender)
{
  if (!this->btn_Re->Down) this->btn_Re->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  fft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));

  RefreshImage(Image,actReal);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dimag3Click(TObject *Sender)
{

  if (!this->btn_Re->Down) this->btn_Re->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  fft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));

  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();


}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Dreal1Click(TObject *Sender)
{
WORD m;

 if (!this->btn_Re->Down) this->btn_Re->Down=true;
 if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
 DisableAllButtons();

for (m=0;m<Nz;m++)
    ifft2(aCplxEnvelope[m],aCplxImage[m],order(Ny),order(Nx));

  RefreshImage(Image,actReal);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Dimag1Click(TObject *Sender)
{
WORD m;

 if (!this->btn_Re->Down) this->btn_Re->Down=true;
 if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
 DisableAllButtons();


for (m=0;m<Nz;m++)
    ifft2(aCplxEnvelope[m],aCplxImage[m],order(Ny),order(Nx));

  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();



}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dreal2Click(TObject *Sender)
{
  
  if (!this->btn_Re->Down) this->btn_Re->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  ifft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));

  RefreshImage(Image,actReal);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Dimag2Click(TObject *Sender)
{

  if (!this->btn_Im->Down) this->btn_Im->Down=true;
  if (!counted[n_sign]) {ShowMessage(msgSig);return;};//ZPRÁVA : není vypoèítán  signál
  DisableAllButtons();

  ifft3(aCplxEnvelope,aCplxImage,order(Nz),order(Ny),order(Nx));

  RefreshImage(Image,actImag);
  this->RefreshLabels();
  counted[n_reko]=0;

  EnableAllButtons();


	
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Histogram1Click(TObject *Sender)
{
 Hist->Show();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetPhaseClick(TObject *Sender)
{
  RefPhase->Show();
}
//---------------------------------------------------------------------------
