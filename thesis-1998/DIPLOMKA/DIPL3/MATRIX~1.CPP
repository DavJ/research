#ifndef _matrix_io
#define _matrix_io

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma  hdrstop
#include <complex.h>
#include "const.cpp"
#include "alloc_nd.hpp"
//---------------------------------------------------------------------------
#define  extension "dat"       	//pøípona datových souborù
//extern  Nx,Ny,Nz;
 /*#ifndef huge
  #define huge
 #endif  */



typedef struct {
 void    **mat; //pointer na matici
 char    *name; //jméno souboru pro uložení/nahrátí matice
 WORD     Ny,Nx; //rozmìry matice
 BYTE     IsComplex;
 } MATRIX ;

MATRIX aktual={NULL,NULL,64,64,0};

void SaveMatrix(MATRIX matr)
{
  WORD i,j;
  FILE *fw;
  char filename[256];


 strcat(strcat(strcpy(filename,matr.name),"."),extension);

  fw=fopen(filename,"w");
  for (i=0;i<matr.Ny;i++)
    {
     for (j=0;j<matr.Nx;j++)
       {
        if (matr.IsComplex) {
	       if(real(((complex**)matr.mat)[i][j])>=0) putc(' ',fw);
	       fprintf(fw,"%le \t",real(((complex**)matr.mat)[i][j]));
	       if(imag(((complex**)matr.mat)[i][j])>=0) putc(' ',fw);
	       fprintf(fw,"%le \t\t",imag(((complex**)matr.mat)[i][j]));
                             }
         else {
   	       if(((double**)matr.mat)[i][j]>=0) putc(' ',fw);
	       fprintf(fw,"%le \t",((double**)matr.mat)[i][j]);
           fprintf(fw,"%le \t\t",0.0);
               }
        }

     fprintf(fw,"\n");
    }
  fclose(fw);
}

void LoadMatrix(MATRIX matr)
{
  FILE *fr;
  WORD  i,j;
  double pom;
  char filename[256];

 strcat(strcat(strcpy(filename,matr.name),"."),extension);

  fr=fopen(filename,"r");
  for (i=0;i<matr.Ny;i++)
    for (j=0;j<matr.Nx;j++)
      {
	    fscanf(fr,"%lf",&pom);
        if (matr.IsComplex)((complex**)matr.mat)[i][j]=complex(pom,0);  //realna cast
         else ((double**)matr.mat)[i][j]=pom;

    	fscanf(fr,"%lf",&pom);
        if (matr.IsComplex)((complex**)matr.mat)[i][j]+=complex(0,pom);//imaginarni cast

       }
  fclose(fr);
}

//--------------------------------------------------------------

//-----------------------------------------------------------------------
/* ze souboru 'infile' (typu *.nmr) nahraje globální promìnné Nx,Ny,Ny
   a alokuje a nahraje tkáò jejíž hodnotu vrací,
   funkce smí být vyvolána až po volání funkce DeallocAll(Nz)*/

TISSUE LoadTissue(FILE *infile)
{
 WORD i,j,k;

 float T1,T2,M0;

 TISSUE Tissue;

 fread(&Nx,sizeof(WORD),1,infile);
 fread(&Ny,sizeof(WORD),1,infile);
 fread(&Nz,sizeof(WORD),1,infile);



Tissue.T1= FloatAlloc_3D(Nz,Ny,Nx);
Tissue.T2= FloatAlloc_3D(Nz,Ny,Nx);
Tissue.M0= FloatAlloc_3D(Nz,Ny,Nx);

 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
       fread(&T1,sizeof(float),1,infile);
       fread(&T2,sizeof(float),1,infile);
       fread(&M0,sizeof(float),1,infile);

       Tissue.T1[k][j][i]=T1;
       Tissue.T2[k][j][i]=T2;
       Tissue.M0[k][j][i]=M0;
      }

 return (Tissue);
}

//-----------------------------------------------------------------------
/* ze souboru 'infile' (typu *.cpl) nahraje globální promìnné Nx,Ny,Ny
   a alokuje a nahraje komplexní 3D pole, na které vrátí ukazatel
   funkce smí být vyvolána až po volání funkce DeallocAll(Nz)*/

complex huge ***LoadCplx(FILE *infile)
{
 WORD i,j,k;
// WORD Nx,Ny,Nz;
 complex huge ***cplx_3D;

 fread(&Nx,sizeof(WORD),1,infile);
 fread(&Ny,sizeof(WORD),1,infile);
 fread(&Nz,sizeof(WORD),1,infile);

 cplx_3D= CplxAlloc_3D(Nz,Ny,Nx);

 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
       fread(&cplx_3D[k][j][i],sizeof(complex),1,infile);
      }

 return (cplx_3D);
}
//-----------------------------------------------------------------------
/* do souboru 'outfile' (typu *.cpl) nahraje globální promìnné Nx,Ny,Ny
   a komplexní 3D pole clpx_3D*/

void SaveCplx(FILE *outfile,WORD Nz,WORD Ny,WORD Nx,complex huge ***cplx_3D)
{
 WORD i,j,k;

 fwrite(&Nx,sizeof(WORD),1,outfile);
 fwrite(&Ny,sizeof(WORD),1,outfile);
 fwrite(&Nz,sizeof(WORD),1,outfile);

 //if (!cplx_3D)
 for(k=0;k<Nz;k++)
   for(j=0;j<Ny;j++)
      for(i=0;i<Nx;i++)
      {
       fwrite(&cplx_3D[k][j][i],sizeof(complex),1,outfile);
      }
}




#endif
