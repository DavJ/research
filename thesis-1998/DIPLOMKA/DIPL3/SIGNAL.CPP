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
1) P�ed za��tkem buzen� a gradient� tj. v �ase  0
2) B�hem  posledn�ho impulsu tedy pro  se prov�d� "sn�m�n� a vzorkov�n�" sign�lu
   NMR p�i�em� je respektov�na p��tomnost gradient� pole  G[NI-1]
3) Vzorkov�n� sign�lu se prov�d�  s periodou Ts, po�et vzork� je Ns
4) Impulsy mg. pole jsou konstantn� v �asov�ch intervalech
   <0,t[0]),<t[0],t[0]+t[1])...<t[0]+t[1]+.. t[NI-2],t[0]+t[1]+..t[NI-2]+t[NI-1])

5) Gradienty pol� G[n].x,G[n].y,G[n].z nejsou ud�ny v jednotk�ch [T/m]
   n�br� jsou vzta�eny na jednotku indexu v dan�m sm�ru,tj. jde o sou�in
   gradientu v [T/m] a vzorkovac� vzd�lenosti Xs,Ys nebo Zs

   odchylka mg. pole od statick�ho B0 se ur�� jako:
       dB0[n]=(k-(Nelemz-1)/2)*G[n].z+(i-(Nelemy-1)/2)*G[n].y+(j-(Nelemx-1)/2)*G[n].x

*/

//---------------------------------------------------------------------------
//sb�r sign�lu z cel� 3D tk�n�
void signal_3D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexn�ho vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts) //pocet cas vzorku,vzorkovaci perioda
{
 WORD     i,j,k,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulov�n� sign�lu


 for (k=0;k<Nz;k++)
   {
   iz=(double)k-(Nz-1)/2.0;
   for (j=0;j<Ny;j++)
     {
     iy=(double)j-(Ny-1)/2.0;
     for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // v�po�et po��te�n�ch podm�nek na za��tku sn�mac�ho impulsu mg.pole
       for (n=0;n<Field.NS-1;n++)
         {
          dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

          if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
        else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
         }

    //sn�m�n� a vzorkov�n� sign�lu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);

       // v�po�et po��te�n�ch podm�nek pro dal�� sekvenci impuls� mg.pole
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
//sb�r sign�lu z cel� 3D tk�n�, ide�ln� 90-stup�ov� RF
void sig90_3D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexn�ho vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts) //pocet cas vzorku,vzorkovaci perioda

{

 WORD i,j,k,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulov�n� sign�lu

 for (k=0;k<Nz;k++)
   {
   iz=(double)k-(Nz-1)/2.0;
   for (j=0;j<Ny;j++)
     {
     iy=(double)j-(Ny-1)/2.0;
     for (i=0;i<Nx;i++)
       {
       ix=(double)i-(Nx-1)/2.0;

       // v�po�et f�zov�ho k�dov�n� (mus� b�t rovno Ngy==Ngz)
       dB0=ix*Field.Gx[Field.Ngy-1]+iy*Field.Gy[Field.Ngy-1]+iz*Field.Gz[Field.Ngy-1];
       solut0(&Mbeg[k][j][i],Field.t[Field.Ngy-1],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);

    //sn�m�n� a vzorkov�n� sign�lu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);
     }
   }
  }
};

//sb�r sign�lu z vybran�ho 2D slidu tk�n�
void signal_2D(/*OUTPUT*/ complex Mxy[],   //casovy prubeh komplexn�ho vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts,WORD k) //pocet cas vzorku,vzorkovaci perioda
{
 WORD     i,j,n;
 double   dB0;
 double   ix,iy,iz;

 for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulov�n� sign�lu

  iz=(double)k-(Nz-1)/2.0;
  for (j=0;j<Ny;j++)
    {
    iy=(double)j-(Ny-1)/2.0;
    for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // v�po�et po��te�n�ch podm�nek na za��tku sn�mac�ho impulsu mg.pole
       for (n=0;n<Field.NS-1;n++)
         {
          dB0=ix*Field.Gx[n]+iy*Field.Gy[n]+iz*Field.Gz[n];

          if (Field.B1[n]==0) solut0(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);
        else solut1R(&Mbeg[k][j][i],Field.t[n],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],Field.B1[n],dB0);
        }

    //sn�m�n� a vzorkov�n� sign�lu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);

    // v�po�et po��te�n�ch podm�nek pro dal�� sekvenci impuls� mg.pole
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
//sb�r sign�lu z vybran�ho 2D slidu tk�n�,ide�ln� 90-stup�ov� RF
void sig90_2D(/*OUTPUT*/complex Mxy[],   //casovy prubeh komplexn�ho vektoru magnetizace v dobe detekce
              /*INPUT*/WORD Ns,float Ts,WORD k) //pocet cas vzorku,vzorkovaci perioda

{
WORD     i,j,n;
double   dB0;
double   ix,iy,iz;
SPACE    Mp;


for (n=0;n<Ns;n++)   Mxy[n]=0; //vynulov�n� sign�lu
  iz=(double)k-(Nz-1)/2.0;

  for (j=0;j<Ny;j++)
    {
    iy=(double)j-(Ny-1)/2.0;
    for (i=0;i<Nx;i++)
      {
       ix=(double)i-(Nx-1)/2.0;

       // v�po�et f�zov�ho k�dov�n� (mus� b�t rovno Ngy==Ngz)
       dB0=ix*Field.Gx[Field.Ngy-1]+iy*Field.Gy[Field.Ngy-1]+iz*Field.Gz[Field.Ngy-1];
       solut0(&Mbeg[k][j][i],Field.t[Field.Ngy-1],Mbeg[k][j][i],Tissue.T1[k][j][i],Tissue.T2[k][j][i],Tissue.M0[k][j][i],dB0);

    //sn�m�n� a vzorkov�n� sign�lu
    dB0=ix*Field.Gx[Field.NS-1]+iy*Field.Gy[Field.NS-1]+iz*Field.Gz[Field.NS-1];
    AddSignal0(Mxy,Ts,Ns,Mbeg[k][j][i],Tissue.T2[k][j][i],dB0);
   }
  }
};


//z�sk� komplexn� obraz z 3D k�dovan� komplexn� ob�lky
void GetImage33D(complex ***Image,complex  ***CplxEnvelope,WORD Nz,WORD Ny,WORD Nx)
{
complex ***aS;		//komplexn� ob�lka sign�lu
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

//z�sk� komplexn� obraz z 2D k�dovan� komplexn� ob�lky
void GetImage32D(complex ***Image,complex  ***CplxEnvelope,WORD Nz,WORD Ny,WORD Nx)
{
complex **aS;		//komplexn� ob�lka sign�lu
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

//provede 3D  korekci posuvu modulac� komplexn� ob�lky
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




//provede 2D  korekci posuvu modulac� komplexn� ob�lky

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

//---------------------inicializace po��te�n�ch podm�nek------------------------------------------------------
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
//z�sk� sign�l z 3D tk�n� pomoc� 3D k�dov�n�m
void  GetSignal33D(int bgcnd)
{
  WORD l,m;							//indexy f�zov�ho k�dov�n�
  Progress->InitProgress(Nz*Ny);				       //nastaven� ukazatele progrese v�po�tu

if (bgcnd==begRR)
  {
   InitBegCond();     	 //inicializace po��te�n�ch podm�nek

   for (m=0;m<Nz;m++)				//smy�ka f�zov�ho k�dov�n�  z
      {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
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
   for (m=0;m<Nz;m++)				//smy�ka f�zov�ho k�dov�n�  z
      {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
       {
        InitBegCond();          //POKA�D� ! inicializace po��te�n�ch podm�nek
        Field.Gy[Field.Ngy-1]=Field.gy0*l;Field.Gz[Field.Ngz-1]=Field.gz0*m;
        signal_3D(aCplxEnvelope[m][l],Nx,Ts);
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
      }
  }  //end begIR

if (bgcnd==beg90)
  {
   for (m=0;m<Nz;m++)				//smy�ka f�zov�ho k�dov�n�  z
      {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
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
  if (Progress->Broken) MainForm->ShowMessage(msgBreak);//zpr�va p�eru�en� v�po�tu
}

//---------------------------------------------------------------------------
//z�sk� sign�l z 3D tk�n� pomoc� selektivn�ho v�b�ru slidu a 2D k�dov�n�
void  GetSignal32D(int bgcnd)
{
 WORD l,m;							//m-index f�zov�ho k�dov�n�,m-index v�b�ru slidu

 Progress->InitProgress(Nz*Ny);				//nastaven� ukazatele progrese v�po�tu

 if (bgcnd==begRR)
   {
   InitBegCond();     	 //inicializace po��te�n�ch podm�nek
   for (m=0;m<Nz;m++)				//smy�ka v�b�ru slidu   z
     {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
       {
        Field.Gy[Field.Ngy-1]=Field.gy0*l;
        Field.Gz[Field.Ngz-1]=0;//��dn� f�zov� k�dovac� gradient ve sm�ru z
        signal_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sb�r sign�lu z m-t�ho slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end begRR

 if (bgcnd==begIR)
   {

   for (m=0;m<Nz;m++)				//smy�ka v�b�ru slidu   z
     {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
       {
        InitBegCond();     	 //POKA�D� !  inicializace po��te�n�ch podm�nek
        Field.Gy[Field.Ngy-1]=Field.gy0*l;
        Field.Gz[Field.Ngz-1]=0;//��dn� f�zov� k�dovac� gradient ve sm�ru z
        signal_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sb�r sign�lu z m-t�ho slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end begIR

 if (bgcnd==beg90)
   {

   for (m=0;m<Nz;m++)				//smy�ka v�b�ru slidu   z
     {
     for (l=0;l<Ny;l++)				//smy�ka f�zov�ho k�dov�n�  y
       {
        InitBegCond90();
        Field.Gy[Field.Ngy-1]=Field.gy0*l;;
        Field.Gz[Field.Ngz-1]=0;//��dn� f�zov� k�dovac� gradient ve sm�ru z
        sig90_2D(aCplxEnvelope[m][l],Nx,Ts,m);  //2D sb�r sign�lu z m-t�ho slidu
        Progress->Increment();if (Progress->Broken) break;
       }
     if (Progress->Broken) break;
     }
    }//end beg90

  Progress->Hide();
  if (Progress->Broken) MainForm->ShowMessage(msgBreak);//zpr�va p�eru�en� v�po�tu

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



