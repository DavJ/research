//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "io_data.h"
#include "Const_BE.cpp"
#include "ImProc_BE.cpp"
//---------------------------------------------------------------------------
void CountNMRParams(BYTE index,float tcelsius,float *T1,float *T2,float *M0)
{
  *T1=LookUp[index].T1*(1+LookUp[index].kT1*(tcelsius-Temp));
  *T2=LookUp[index].T2*(1+LookUp[index].kT2*(tcelsius-Temp));
  *M0=LookUp[index].Nprot*mi*tanh(mi*B0/(Kboltz*(tcelsius+Temp0))); //stejnosmerna magnetizace;
}

void savenmr(FILE *outfile)
{
WORD i,j,k;
BYTE index;
float tcelsius;
float M0,T1,T2;

fwrite(&Nx,sizeof(WORD),1,outfile);
fwrite(&Ny,sizeof(WORD),1,outfile);
fwrite(&Nz,sizeof(WORD),1,outfile);

 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
      CountNMRParams(aBody[k][j][i],aTemp[k][j][i],&T1,&T2,&M0);

      fwrite(&T1,sizeof(float),1,outfile);
      fwrite(&T2,sizeof(float),1,outfile);
      fwrite(&M0,sizeof(float),1,outfile);
      }
}

void savebod(FILE *outfile)
{
WORD i,j,k;
BYTE index;
//uložení rozmìrù
fwrite(&Nx,sizeof(WORD),1,outfile);
fwrite(&Ny,sizeof(WORD),1,outfile);
fwrite(&Nz,sizeof(WORD),1,outfile);
//uložení  souvislosti indexù a tkání
for (i=0;i<256;i++)
  {
       fwrite(&i,sizeof(BYTE),1,outfile);  //zápis indexu
       fwrite(LookUp[i].tissue,LTISSUE,1,outfile); //zápis jména odpovídající tkánì
  }

 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
       fwrite(&aBody[k][j][i],sizeof(BYTE),1,outfile);  //zápis indexu tkánì
       fwrite(&aTemp[k][j][i],sizeof(float),1,outfile); //zápis teploty
      }
}

void loadbod(FILE *infile)
{
WORD i,j,k;
BYTE index;
int  ind2;
float temp;
BYTE UseBackground[256];
char Names[256][LTISSUE];
//ètení rozmìrù
fread(&Nx,sizeof(WORD),1,infile);
fread(&Ny,sizeof(WORD),1,infile);
fread(&Nz,sizeof(WORD),1,infile);


  aBody=ByteAlloc_3D(Nz,Ny,Nx);     //alokace nových polí
  aTemp=FloatAlloc_3D(Nz,Ny,Nx);
  aView=ByteAlloc_2D(Ny,Nx);

  Slider->Min=0;
  Slider->Max=Nz-1;
  PosX=0;PosY=0;PosZ=0; //nastavení nové pozice v tìlese
  Slider->Position=0;  //nastavení pozice slideru
  if (Nz==1) Slider->Visible=false; else Slider->Visible=true; //zakáže scroll-bar u 2D tìlesa


//ètení souvislosti indexù a tkání
for (i=0;i<256;i++)
  {
       fread(&index,sizeof(BYTE),1,infile);  //ètení indexu
       fread(Names[index],LTISSUE,1,infile); //ètení jména odpovídající tkánì
       UseBackground[i]=false; //nepoužívat automaticky pozadí pøi nenalezení i-té tkánì
  }

 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
       fread(&index,sizeof(BYTE),1,infile);  //ètení indexu tkánì
       fread(&aTemp[k][j][i],sizeof(float),1,infile); //ètení teploty
       //je-li tkáò nalezena v look-up table
       if ((ind2=GetIndex(Names[index]))>=0) aBody[k][j][i]=ind2; //použij index odpovídající index z aktuální vyhledávací tabulky
        else {
              if (UseBackground[index]==false) Application->MessageBox(Names[index],"Výstraha - tkáò nenalezena v databázi",MB_OK);
              UseBackground[index]=true; //používat automaticky pozadí pøi nenalezení index-té tkánì
             }

      }
}

