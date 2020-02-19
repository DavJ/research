#define  huge
#include <alloc.h>
#include  <complex.h>
//tato funkce vytvari v pameti dvourozmerne dynamicke pole
//velikosti Nx krat Ny

double huge **Alloc_2D(long int Ny,long int Nx)
{
  int i;
  double huge **p;
  double huge * p1;

  if ((p=(double huge * *)calloc(Ny,sizeof(double huge*)))==NULL) return(NULL);

  if ((p1=(double huge*)farcalloc(Nx*Ny,sizeof(double)))==NULL) return (NULL);

  for(i=0;i<Ny;i++)
    {p[i]=p1+i*Nx;}
//pozn. logicka chyba v pripade nealokace jednoho prvku zustane zbytek alokovany!!!
  return(p);
}

void Dealloc_2D(double huge **pointer,long int Ny,long int Nx)
{
     farfree(pointer[0]);
     free(pointer);
}


complex huge *( *CplxAlloc_2D(long int Ny,long int Nx))
{
  int i;
  complex huge **p;
  complex huge * p1;

  if ((p=(complex huge * *)calloc(Ny,sizeof(complex huge*)))==NULL) return(NULL);

  if ((p1=(complex huge *)farcalloc(Nx*Ny,sizeof(complex huge)))==NULL) return (NULL);

  for(i=0;i<Ny;i++)
    {p[i]=p1+i*Nx;}
//pozn. logicka chyba v pripade nealokace jednoho prvku zustane zbytek alokovany!!!
  return(p);
}



void CplxDealloc_2D(complex huge **pointer,long int Ny,long int Nx)
{
     farfree(pointer[0]);
     free(pointer);
}