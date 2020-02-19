#ifndef alokace_n_rozm
#define alokace_n_rozm

#define huge        //jen pro C++ Builder
#include <alloc.h>
#include  <complex.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char huge **Alloc_2Da(WORD Ny,WORD Nx,BYTE size)
{
  WORD i;
  char huge **p;
  char huge *p1;

  if ((p=(char huge **)calloc(Ny,sizeof(char huge*)))==NULL) return(NULL);

 // if ((p1=(char huge*)farcalloc(Nx*Ny,size))==NULL) return (NULL);
   if ((p1=(char huge*)farcalloc(Nx*Ny,size))==NULL)
     {
      MessageBox(NULL,"Neni alokovana pamet ","message",MB_OK);
      exit(0);
     }


  for(i=0;i<Ny;i++)
    {p[i]=p1+i*size*Nx;}
//pozn. logicka chyba v pripade nealokace jednoho prvku zustane zbytek alokovany!!!
  return(p);
}

void Dealloc_2Da(char huge **pointer)
{
     farfree(pointer[0]);
     free(pointer);
}

char ***Alloc_3Da(WORD Nz,WORD Ny,WORD Nx,BYTE size)
{
  WORD i;
  char ***p;       //pointer na tìleso


  if ((p=(char huge ***)calloc(Nz,sizeof(char huge **)))==NULL) return(NULL);

  for(i=0;i<Nz;i++)
    {
     if ((p[i]=Alloc_2Da(Ny,Nx,size))==NULL) return (NULL);
    }
//pozn. logicka chyba v pripade nealokace jednoho prvku zustane zbytek alokovany!!!
  return(p);
}

void Dealloc_3Da(char huge ***pointer,BYTE Nz)
{
  WORD i;
    for(i=0;i<Nz;i++)
       Dealloc_2Da(pointer[i]);

    free(pointer);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//tato funkce vytvari v pameti dvourozmerne dynamicke pole
//velikosti Nx krat Ny
double huge **FloatAlloc_2D(WORD Ny,WORD Nx)
{
  return((double huge **) Alloc_2Da(Ny,Nx,sizeof(double)));
}

void FloatDealloc_2D(double huge **pointer)
{
   Dealloc_2Da((char **)pointer);
}

double huge **DoubleAlloc_2D(WORD Ny,WORD Nx)
{
  return((double huge **) Alloc_2Da(Ny,Nx,sizeof(double)));
}

void DoubleDealloc_2D(double huge **pointer)
{
   Dealloc_2Da((char **)pointer);
}


complex huge *( *CplxAlloc_2D(WORD Ny,WORD Nx))
{
  return((complex huge **) Alloc_2Da(Ny,Nx,sizeof(complex)));
}



void CplxDealloc_2D(complex huge **pointer)
{
    Dealloc_2Da((char **)pointer);
}


BYTE huge **ByteAlloc_2D(WORD Ny,WORD Nx)
{
  return((BYTE huge **) Alloc_2Da(Ny,Nx,sizeof(BYTE)));
}

void ByteDealloc_2D(BYTE huge **pointer)
{
    Dealloc_2Da((char **)pointer);
}

//------------------------- 2D -----------------------------
WORD **WordAlloc_2D(WORD Ny,WORD Nx)
{
return((WORD huge **) Alloc_2Da(Ny,Nx,sizeof(WORD)));
}

void WordDealloc_2D(WORD huge **pointer)
{
  Dealloc_2Da((char **)pointer);
}



//------------------------- 3D -----------------------------
BYTE ***ByteAlloc_3D(WORD Nz,WORD Ny,WORD Nx)
{
 return((BYTE huge ***) Alloc_3Da(Nz,Ny,Nx,sizeof(BYTE)));
}

void ByteDealloc_3D(BYTE huge ***pointer,BYTE Nz)
{
  Dealloc_3Da((char ***)pointer,Nz);
}


WORD ***WordAlloc_3D(WORD Nz,WORD Ny,WORD Nx)
{
 return((WORD huge ***) Alloc_3Da(Nz,Ny,Nx,sizeof(WORD)));
}

void WordDealloc_3D(WORD huge ***pointer,WORD Nz)
{
  Dealloc_3Da((char ***)pointer,Nz);
}


float ***FloatAlloc_3D(WORD Nz,WORD Ny,WORD Nx)
{
 return((float huge ***) Alloc_3Da(Nz,Ny,Nx,sizeof(float)));
}

void FloatDealloc_3D(float huge ***pointer,BYTE Nz)
{
  Dealloc_3Da((char ***)pointer,Nz);
}

double ***DoubleAlloc_3D(WORD Nz,WORD Ny,WORD Nx)
{
 return((double huge ***) Alloc_3Da(Nz,Ny,Nx,sizeof(double)));
}

void DoubleDealloc_3D(double huge ***pointer,BYTE Nz)
{
  Dealloc_3Da((char ***)pointer,Nz);
}


complex ***CplxAlloc_3D(WORD Nz,WORD Ny,WORD Nx)
{
 return((complex huge ***) Alloc_3Da(Nz,Ny,Nx,sizeof(complex)));
}

void CplxDealloc_3D(complex huge ***pointer,BYTE Nz)
{
  Dealloc_3Da((char ***)pointer,Nz);
}


#endif
