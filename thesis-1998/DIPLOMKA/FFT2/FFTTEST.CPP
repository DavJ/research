#include <stdio.h>
#include <stdlib.h>
#include "fft2.hpp"
#include <alloc.h>
//#include <complex.h>
//#define  m 3
int m1,m2,tisk;
double huge **s;
complex huge * (*f),huge * (*ft);


void ctisignal(const char *filename,double huge **p)
{
  FILE *fr;
  int  i,j;
  fr=fopen(filename,"r");
  for (i=0;i<(1<<m1);i++)      //
    for (j=0;j<(1<<m2);j++)
      fscanf(fr,"%lf",&p[i][j]);
  fclose(fr);
}


void pissignal(const char *filename,double huge **p)
{
  FILE *fw;
  int  i,j;
  fw=fopen(filename,"w");
  for (i=0;i<(1<<m1);i++)      //
    for (j=0;j<(1<<m2);j++)
         {
   	   if (tisk) printf("%le \t\t",p[i][j]);
	   if(p[i][j]>=0) putc(' ',fw);
	   fprintf(fw,"%le \t",p[i][j]);
         }

  fclose(fw);
}


void ctifft(const char *filename,complex huge **p)
{
  FILE *fr;
  int  i,j;
  double pom;
  fr=fopen(filename,"r");
  for (i=0;i<(1<<m1);i++)
    for (j=0;j<(1<<m2);j++)
      {
	fscanf(fr,"%lf",&pom);
	p[i][j]=complex(pom,0);               //realna cast
	fscanf(fr,"%lf",&pom);
	p[i][j]=p[i][j]+complex(0,pom);      //imaginarni cast
       }
  fclose(fr);
}
void pisfft(const char *filename,complex huge **p)
{
  int i,j;
  FILE *fw;

  fw=fopen(filename,"w");
  for (i=0;i<(1<<m1);i++)
    {
     for (j=0;j<(1<<m2);j++)
       {
	 if (tisk) printf("%le \t %le \t\t",real(p[i][j]),imag(p[i][j]));
	 if(real(p[i][j])>=0) putc(' ',fw);
	 fprintf(fw,"%le \t",real(p[i][j]));
	 if(imag(p[i][j])>=0) putc(' ',fw);
	 fprintf(fw,"%le \t\t",imag(p[i][j]));
       }
     if (tisk) printf("\n");
     fprintf(fw,"\n");
    }
  fclose(fw);
}




double  sumerr()
{
  double se=0;
  int  i,j;
  for (i=0;i<(1<<m1);i++)
    for (j=0;j<(1<<m2);j++)
      {
	se+=abs(f[i][j]-ft[i][j]);
      }
return se;
}

void konec(int i)
{
 printf("\n Program ukoncen chybou: %d",i);
 exit(0);
}


void fmain()
{
  printf("Zadej rad fft ve svislem smeru:");
  scanf("%d",&m1);
  printf("\nZadej rad fft ve vodorovnem smeru:");
  scanf("%d",&m2);
  printf("\n");

  printf("Tisknout na obrazovku vypis (A/N) ?");
  tisk=((getchar()=='A')||(getchar()=='a'));

  if((f=CplxAlloc_2D((1<<m1),(1<<m2)))==NULL) {konec(2);}
  if((s=Alloc_2D((1<<m1),(1<<m2)))==NULL) {konec(1);}
  if((ft=CplxAlloc_2D((1<<m1),(1<<m2)))==NULL) {konec(3);}

  ctisignal("e:/borlandc/david/fft2/input.txt",s);
  pissignal("e:/borlandc/david/fft2/sgn_tst.txt",s);

  ctifft("e:/borlandc/david/fft2/output.txt",ft);
  pisfft("e:/borlandc/david/fft2/fft_tst.txt",ft);
  printf("Error kod fft2 0==OK : %d \n",fft2(s,f,m1,m2));
  pisfft("e:/borlandc/david/fft2/fft_out.txt",f);
  printf("Celkova  suma chyb: %lf \n",sumerr());

  Dealloc_2D(s,(1<<m1),(1<<m2));
  CplxDealloc_2D(f,(1<<m1),(1<<m2));
  CplxDealloc_2D(ft,(1<<m1),(1<<m2));

}
