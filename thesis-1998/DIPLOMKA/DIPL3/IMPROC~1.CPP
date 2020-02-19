//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop


#include "signal.cpp"
#include "values.h"
#include <complex.h>
//#include "matrix_io.cpp"
//---------------------------------------------------------------------------

//vypocet palety cb. obrazu s n_grays odstiny sedi

HPALETTE Shades(BYTE n_grays)
{
  HPALETTE Palette;  //pomocna promenna
  BYTE i,k;
  LOGPALETTE* plgpl;

plgpl=(LOGPALETTE*)LocalAlloc(LPTR,sizeof(LOGPALETTE)+n_grays*sizeof(PALETTEENTRY));
plgpl->palNumEntries = n_grays;
plgpl->palVersion = 0x300;

k=(BYTE)255/(n_grays-1);/*nasobny koeficient pro maximalni kontrast
	     		     musi byt celistve cislo pro rovnomernou
                             stupnici sedi*/

    for (i = 0; i<(n_grays);i++) {
      plgpl->palPalEntry[i].peRed =k*i;
      plgpl->palPalEntry[i].peGreen =k*i;
      plgpl->palPalEntry[i].peBlue = k*i;
      plgpl->palPalEntry[i].peFlags =PC_NOCOLLAPSE;//NULL;
      };

    Palette = CreatePalette(plgpl);
    LocalFree((HLOCAL) plgpl);
    return  Palette;
}






//pozor zmena argumentu Nx <-> Ny oproti puvodni verzi s pointery
//navíc místo double float

void Histogram(double huge **in,BYTE huge **out,unsigned int Ny,unsigned int Nx)
{
  unsigned int i,j;
  BYTE Black;
  double delt,smer;
  HistMin=MAXDOUBLE;			//inicializace maximalni a minimalni hodnoty
  HistMax=-MAXDOUBLE;

//urceni parametru linearni prevodni charakteristiky pro max. kontrast
  for (i=0;i<Ny;i++)
    for (j=0;j<Nx;j++)
    {
      if (in[i][j]<HistMin) HistMin=in[i][j];
      if (in[i][j]>HistMax) HistMax=in[i][j];
    }

   delt=HistMax-HistMin;
   Black=N_COLORS;//index cerne barvy v palete definovan v const.cpp
   switch (HistType){

   case hisLin:   if (delt==0) {smer=0;HistMin=0;} //smernice ;1 da stejne 0;
   								//pozor HistMin by jinak bylo plus nekonecno ->preteceni
                  else smer=(N_SHADES-1)/delt;

                   //zmena histogramu a prevedeni double -> BYTE
                  for (i=0;i<Ny;i++)
                    for (j=0;j<Nx;j++)
                       out[i][j]=((in[i][j]-HistMin)*smer)+Black;
                  break;
   case hisLog:   if (delt==0) {smer=0;HistMin=0;} //smernice ;1 da stejne 0;
                  else smer=1/delt;

                  delt=pow(HistLog,N_SHADES-1)-1;
                   //zmena histogramu a prevedeni double -> BYTE
                  for (i=0;i<Ny;i++)
                    for (j=0;j<Nx;j++)
                       out[i][j]=log(delt*(in[i][j]-HistMin)*smer+1)/log(HistLog)+Black;
                  break;
 			}
 }


void PutToImage(double ** aImage,float ** S,WORD Ny,WORD Nx)
{
  WORD i,j;

  for(j=0;j<Ny;j++)
    for(i=0;i<Nx;i++)
      aImage[j][i]=S[j][i];
}

void Real_2D(double ** aImage,complex  **S,WORD Ny,WORD Nx,double Phase)
{
  WORD i,j;
  double phase_rad=Phase*Pi/180;

  for(j=0;j<Ny;j++)
    for(i=0;i<Nx;i++)
      aImage[j][i]=real(S[j][i]*exp(complex(0,-phase_rad)));
}

void Imag_2D(double ** aImage,complex  **S,WORD Ny,WORD Nx,double Phase)
{
  WORD i,j;
  double phase_rad=Phase*Pi/180;

  for(j=0;j<Ny;j++)
    for(i=0;i<Nx;i++)
      aImage[j][i]=imag(S[j][i]*exp(complex(0,-phase_rad)));
}


