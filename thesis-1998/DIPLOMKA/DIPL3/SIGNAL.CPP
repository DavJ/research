//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "const.cpp"
//---------------------------------------------------------------------------
#include <math.h>
#include "analyt.hpp"
#include "fft2.hpp"
#include "prog.cpp"

/*
Pozn:
1) Pøed zaèátkem buzení a gradientù tj. v èase  0
2) Bìhem  posledního impulsu tedy pro  se provádí "snímání a vzorkování" signálu
   NMR pøièemž je respektována pøítomnost gradientù pole  G[NI-1]
3) Vzorkování signálu se provádí  s periodou Ts, poèet vzorkù je Ns
4) Impulsy mg. pole jsou konstantní v èasových intervalech
   <0,t[0]),<t[0],t[0]+t[1])...<t[0]+t[1]+.. t[NI-2],t[0]+t[1]+..t[NI-2]+t[NI-1])

5) Gradienty polí G[n].x,G[n].y,G[n].z nejsou udány v jednotkách [T/m]
   nýbrž jsou vztaženy na jednotku indexu v daném smìru,tj. jde o souèin
   gradientu v [T/m] a vzorkovací vzdálenosti Xs,Ys nebo Zs

   odchylka mg. pole od statického B0 se urèí jako:
       dB0[n]=(k-(Nelemz-1)/2)*G[n].z+(i-(Nelemy-1)/2)*G[n].y+(j-(Nelemx-1)/2)*G[n].x

*/

//---------------------------------------------------------------------------
//sbìr signálu z celé 3D tkánì
void signal_3D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexního vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts) //pocet cas vzorku,vzorkovaci perioda
{
 WORD     i,j,k,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulování signálu


 for (k=0;k<Nz;k++)
   {
   iz=(double)k-(Nz-1)/2.0;
   for (j=0;j<Ny;j++)
     {
     iy=(double)j-(Ny-1)/2.0;
     for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // výpoèet poèáteèních podmínek na zaèátku snímacího impulsu mg.pole
       for (n=0;n<Field.NS-1;n++)
         {
          dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

          if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
        else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
         }

    //snímání a vzorkování signálu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);

       // výpoèet poèáteèních podmínek pro další sekvenci impulsù mg.pole
       for (n=Field.NS-1;n<Field.NI;n++)
         {
          dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

          if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
        else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
         }
     }
    }
  }

};

//---------------------------------------------------------------------------
//sbìr signálu z celé 3D tkánì, ideální 90-stupòový RF
void sig90_3D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexního vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts) //pocet cas vzorku,vzorkovaci perioda

{

 WORD i,j,k,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulování signálu

 for (k=0;k<Nz;k++)
   {
   iz=(double)k-(Nz-1)/2.0;
   for (j=0;j<Ny;j++)
     {
     iy=(double)j-(Ny-1)/2.0;
     for (i=0;i<Nx;i++)
       {
       ix=(double)i-(Nx-1)/2.0;

       // výpoèet fázového kódování (musí být rovno Ngy==Ngz)
       dB0=ix*Field.Gx[Field.Ngy-1]+iy*Field.Gy[Field.Ngy-1]+iz*Field.Gz[Field.Ngy-1];
       solut0(&Mbeg[k][j][i],Field.t[Field.Ngy-1],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);

    //snímání a vzorkování signálu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);
     }
   }
  }
};

//sbìr signálu z vybraného 2D slidu tkánì
void signal_2D(/*OUTPUT*/ complex Mxy[],   //casovy prubeh komplexního vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts,WORD k) //pocet cas vzorku,vzorkovaci perioda
{
 WORD     i,j,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulování signálu

  iz=(double)k-(Nz-1)/2.0;
  for (j=0;j<Ny;j++)
    {
    iy=(double)j-(Ny-1)/2.0;
    for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // výpoèet poèáteèních podmínek na zaèátku snímacího impulsu mg.pole
       for (n=0;n<Field.NS-1;n++)
         {
          dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

          if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
        else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
        }

    //snímání a vzorkování signálu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);

    // výpoèet poèáteèních podmínek pro další sekvenci impulsù mg.pole
    for (n=Field.NS-1;n<Field.NI;n++)
      {
         dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

         if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
          else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
      }
  }
 }
};


//---------------------------------------------------------------------------
//sbìr signálu z vybraného 2D slidu tkánì,ideální 90-stupòový RF
void sig90_2D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexního vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts,WORD k) //pocet cas vzorku,vzorkovaci perioda

{
WORD     i,j,n;
double   dB0;
double   ix,iy,iz;
SPACE    Mp;


for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulování signálu
  iz=(double)k-(Nz-1)/2.0;

  for (j=0;j<Ny;j++)
    {
    iy=(double)j-(Ny-1)/2.0;
    for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // výpoèet fázového kódování (musí být rovno Ngy==Ngz)
       dB0=ix*Field.Gx[Field.Ngy-1]+iy*Field.Gy[Field.Ngy-1]+iz*Field.Gz[Field.Ngy-1];
       solut0(&Mbeg[k][j][i],Field.t[Field.Ngy-1],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);

    //snímání a vzorkování signálu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);
   }
  }
};


//získá komplexní obraz z 3D kódované komplexní obálky
void GetImage33D(complex ***Image,complex  ***CplxEnvelope,WORD Nz,WORD Ny,WORD Nx)
{
complex ***aS;		//komplexní obálka signálu
WORD k,l,m;

complex  arg1=complex(0,Pi*(1.0/Nx-1));
complex  arg2=complex(0,Pi*(1.0/Ny-1));
complex  arg3=complex(0,Pi*(1.0/Nz-1));

  aS=CplxAlloc_3D(Nz,Ny,Nx);

 for (m=0;m<Nz;m++)
  for (l=0;l<Ny;l++)
    for (k=0;k<Nx;k++)
      {
        aS[m][l][k]=(aCplxEnvelope[m][l][k])*exp(arg1*k+arg2*l+arg3*m);
      }

 ifft3(aS,aCplxImage,order(Nz),order(Ny),order(Nx));

 CplxDealloc_3D(aS,Nz);
}

//získá komplexní obraz z 2D kódované komplexní obálky
void GetImage32D(complex ***Image,complex  ***CplxEnvelope,WORD Nz,WORD Ny,WORD Nx)
{
complex **aS;		//komplexní obálka signálu
WORD k,l,m;

complex  arg1=complex(0,Pi*(1.0/Nx-1));
complex  arg2=complex(0,Pi*(1.0/Ny-1));


 aS=CplxAlloc_2D(Ny,Nx);

 for (m=0;m<Nz;m++)
   {
    for (l=0;l<Ny;l++)
      for (k=0;k<Nx;k++)
        {
         aS[l][k]=(aCplxEnvelope[m][l][k])*exp(arg1*k+arg2*l);
        }

   ifft2(aS,aCplxImage[m],order(Ny),order(Nx));
   }
 CplxDealloc_2D(aS);
}

//provede 3D  korekci posuvu modulací komplexní obálky
void PhaseCorect3D(complex ***Corected)
{
 WORD k,l,m;

 complex  arg1=complex(0,Pi*(1.0/Nx-1));
 complex  arg2=complex(0,Pi*(1.0/Ny-1));
 complex  arg3=complex(0,Pi*(1.0/Nz-1));

 for (m=0;m<Nz;m++)
   {
    for (l=0;l<Ny;l++)
      for (k=0;k<Nx;k++)
        {
         Corected[m][l][k]=(aCplxEnvelope[m][l][k])*exp(arg1*k+arg2*l+arg3*m);
        }

   }

}




//provede 2D  korekci posuvu modulací komplexní obálky

void PhaseCorect2D(complex ***Corected)
{
 WORD k,l,m;

 complex  arg1=complex(0,Pi*(1.0/Nx-1));
 complex  arg2=complex(0,Pi*(1.0/Ny-1));

 for (m=0;m<Nz;m++)
   {
    for (l=0;l<Ny;l++)
      for (k=0;k<Nx;k++)
        {
         Corected[m][l][k]=(aCplxEnvelope[m][l][k])*exp(arg1*k+arg2*l);
        }

   }
}

//---------------------inicializace poèáteèních podmínek------------------------------------------------------
void InitBegCond()
{
 WORD i,j,k;
 for (k=0;k<Nz;k++)
   for (j=0;j<Ny;j++)
     for (i=0;i<Nx;i++)
       {
         Mbeg[k][j][i].x=0;Mbeg[k][j][i].y=0;Mbeg[k][j][i].z=Tissue.M0[k][j][i];
       }
}

void InitBegCond90()
{
 WORD i,j,k;
 for (k=0;k<Nz;k++)
   for (j=0;j<Ny;j++)
     for (i=0;i<Nx;i++)
       {
         Mbeg[k][j][i].x=0;Mbeg[k][j][i].y=Tissue.M0[k][j][i];Mbeg[k][j][i].z=0;
       }
}



//---------------------------------------------------------------------------
//získá signál z 3D tkánì pomocí 3D kódováním
void  GetSignal33D(int bgcnd)
{
  WORD l,m;							//indexy fázového kódování
  Progress->InitProgress(Nz*Ny);				       //nastavení ukazatele progrese výpoètu

if (bgcnd==begRR)
  {
   InitBegCond();     	 //inicializace poèáteèních podmínek

   for (m=0;m<Nz;m++)				//smyèka fázového kódování  z
      {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        Field.Gy[Field.Ngy-1]=Field.gy0*l;Field.Gz[Field.Ngz-1]=Field.gz0*m;
        signal_3D(aCplxEnvelope[m][l],Nx,Ts);
        Progress->Increment();if (Progress->Broken) break;
       }

     if (Progress->Broken) break;
      }
  }  //end begRR

if (bgcnd==begIR)
  {
   for (m=0;m<Nz;m++)				//smyèka fázového kódování  z
      {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        InitBegCond();          //POKAŽDÉ ! inicializace poèáteèních podmínek
        Field.Gy[Field.Ngy-1]=Field.gy0*l;Field.Gz[Field.Ngz-1]=Field.gz0*m;
        signal_3D(aCplxEnvelope[m][l],Nx,Ts);
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
      }
  }  //end begIR

if (bgcnd==beg90)
  {
   for (m=0;m<Nz;m++)				//smyèka fázového kódování  z
      {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        InitBegCond90();
        Field.Gy[Field.Ngy-1]=Field.gy0*l;Field.Gz[Field.Ngz-1]=Field.gz0*m;
        sig90_3D(aCplxEnvelope[m][l],Nx,Ts);
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
      }
  }  //end beg90

  Progress->Hide();
  if (Progress->Broken) MainForm->ShowMessage(msgBreak);//zpráva pøerušení výpoètu
}

//---------------------------------------------------------------------------
//získá signál z 3D tkánì pomocí selektivního výbìru slidu a 2D kódování
void  GetSignal32D(int bgcnd)
{
 WORD l,m;							//m-index fázového kódování,m-index výbìru slidu

 Progress->InitProgress(Nz*Ny);				//nastavení ukazatele progrese výpoètu

 if (bgcnd==begRR)
   {
   InitBegCond();     	 //inicializace poèáteèních podmínek
   for (m=0;m<Nz;m++)				//smyèka výbìru slidu   z
     {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        Field.Gy[Field.Ngy-1]=Field.gy0*l;
        Field.Gz[Field.Ngz-1]=0;//žádný fázovì kódovací gradient ve smìru z
        signal_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sbìr signálu z m-tého slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end begRR

 if (bgcnd==begIR)
   {

   for (m=0;m<Nz;m++)				//smyèka výbìru slidu   z
     {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        InitBegCond();     	 //POKAŽDÉ !  inicializace poèáteèních podmínek
        Field.Gy[Field.Ngy-1]=Field.gy0*l;
        Field.Gz[Field.Ngz-1]=0;//žádný fázovì kódovací gradient ve smìru z
        signal_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sbìr signálu z m-tého slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end begIR

 if (bgcnd==beg90)
   {

   for (m=0;m<Nz;m++)				//smyèka výbìru slidu   z
     {
     for (l=0;l<Ny;l++)				//smyèka fázového kódování  y
       {
        InitBegCond90();
        Field.Gy[Field.Ngy-1]=Field.gy0*l;;
        Field.Gz[Field.Ngz-1]=0;//žádný fázovì kódovací gradient ve smìru z
        sig90_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sbìr signálu z m-tého slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end beg90

  Progress->Hide();
  if (Progress->Broken) MainForm->ShowMessage(msgBreak);//zpráva pøerušení výpoètu

}

//---------------------------------------------------------------------------
void AllocAll(BYTE Nz,BYTE Ny,BYTE Nx)
{
if (!aView)  aView=ByteAlloc_2D(Ny,Nx);

if (!Tissue.T1)   Tissue.T1= FloatAlloc_3D(Nz,Ny,Nx);
if (!Tissue.T2)   Tissue.T2= FloatAlloc_3D(Nz,Ny,Nx);
if (!Tissue.M0)   Tissue.M0= FloatAlloc_3D(Nz,Ny,Nx);

if (!Mbeg)  	  Mbeg= SpaceAlloc_3D(Nz,Ny,Nx);

if (!aImage)  aImage= DoubleAlloc_2D(Ny,Nx);
if (!aCplxImage) aCplxImage=CplxAlloc_3D(Nz,Ny,Nx);
if (!aCplxEnvelope) aCplxEnvelope=CplxAlloc_3D(Nz,Ny,Nx);

if (Nz==1) Slider->Visible=false; else Slider->Visible=true;
}

//---------------------------------------------------------------------------

void DeallocAll(BYTE Nz)
{
if (aView) {ByteDealloc_2D(aView);aView=NULL;}

if (Tissue.T1) {FloatDealloc_3D(Tissue.T1,Nz);Tissue.T1=NULL;}
if (Tissue.T2) {FloatDealloc_3D(Tissue.T2,Nz);Tissue.T2=NULL;}
if (Tissue.M0) {FloatDealloc_3D(Tissue.M0,Nz);Tissue.M0=NULL;}

if (Mbeg) {SpaceDealloc_3D(Mbeg,Nz);Mbeg=NULL;}

if (aImage) {DoubleDealloc_2D(aImage);aImage=NULL;}

if (aCplxImage) {CplxDealloc_3D(aCplxImage,Nz);aCplxImage=NULL;}
if (aCplxEnvelope) {CplxDealloc_3D(aCplxEnvelope,Nz);aCplxEnvelope=NULL;}

}



