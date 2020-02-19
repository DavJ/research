#ifndef _constincluded

  #define _constincluded
  #define huge			//nutno definovat pro C++ Builder,pro BCW odstranit !!
//---------------------------------------------------------------------------
  #include <vcl\vcl.h>
  #include <complex.h>
  #include "alloc_nd.hpp"
  #pragma hdrstop


//-------------------------------zobrazování (vykreslení)--------------------------------------------
  #define  N_SHADES 128		//poèet odstínù šedé pro vykreslování
  #define  MAX_IMP  30      //maximální poèet impulsù mg.pole
  #define  Nchild   4

  #define  n_tkan   0
  #define  n_sign   1
  #define  n_reko   2
  #define  n_pale   3

  #define  actNO    0
  #define  actM0    1
  #define  actT1    2
  #define  actT2    3

  #define  actMx    4
  #define  actMy    5
  #define  actReal  7
  #define  actImag  8



  #define  msgTis   0
  #define  msgSig   1
  #define  msgBmp   5
  #define  msgBreak 8

  #define  msgNoCpl 7


  #define  FieldUnit 1e-6
  #define  TimeUnit  1e-3
  #define  FreqUnit  1e+6

  #define  GroupRootKey   "NMR Imaging"
  #define  ImagingRootKey "Imaging"

//-------------------------------parametry zobrazovacího systému a jejich default hodnoty --------
  double   deltaB0=0;          //odchylka ss. pole od hodnoty odpovídající RF frekvenci
  double   fsample=2e3;        //vzorkovací frekvence (obálky signálu) [Hz]
  float    Ts=1e-6;            //vzorkovací perioda
  WORD     Nx=8,Ny=8,Nz=8;     //rozmìry tìlesa

  double   HistMin,HistMax;    //minimální a maximální hodnoty histogramu
  #define  hisLin 0
  #define  hisLog 1
  BYTE     HistType=hisLin;          //typ. pøevodní charakteristiky
  float    HistLog=2.718281828459;   //základ logaritmické pøevodní charakteristiky
//-------------------------------fyzikální konstanty--------------------------------------------
  #define  GamaH    2.675e+8  //gyromagnetický koeficient jádra vodíku (protonu)
  #define  Pi  acos(-1)       // 3.142 ...
//-------------------------------default parametry použité zobrazovací metody--------------------------------------------
  BYTE  Method=0,BegCond=2;     //èísla použité zobrazovací metody a poè. podmínek
  BYTE  OldMethod,OldBegCond;  //èísla pøedchozí  použité zobrazovací metody a poè. podmínek
//-------------------------------default parametry testovacího tìlesa--------------------------------------------
  #define   temp 310
  #define   b0 1
  #define  Kboltz 1.38e-23 	//Boltzmanova konstanta
  #define  mi 1.4106e-26        //magnetický moment protonu
  #define  Nprot  6.6887e+28	//densita protonu ve vode [m^(-3)]

  float TestT1a=2.8,TestT2a=0.25,TestM0a=Nprot*mi*tanh(mi*b0/(Kboltz*temp));
  float TestT1b=1.4,TestT2b=0.50,TestM0b=Nprot/2*mi*tanh(mi*b0/(Kboltz*temp));
  WORD  TestNx=8,TestNy=8,TestNz=8;   //rozmìry testovacího tìlesa
  BYTE  TestType=0;                   //typ testovacího tìlesa
  #undef  temp
  #undef  b0
  #undef  Kboltz
  #undef  mi
  #undef  Nprot

//-------------------------------default soubor magnetického pole--------------------------------------------
  char  FieldName[255]="standard.mag";
//-------------------------------default hodnota první barvy--------------------------------------------
  BYTE    N_COLORS=10;		//poèet barev systémové palety(==index èerné barvy po realizaci palety)
//------------------------------ globální promìnné ---------------------------------------------

  BYTE huge **aView;  //pointer to bitmap arrays for bitmap image
  HBITMAP hbmp,hbmppal;
  BYTE    counted[Nchild]={0,0,0,0};

  BYTE aPalette[256][2];
  BITMAP bm;




SPACE ***Mbeg;              //pole poèáteèních podmínek
  
  struct pulse_1D{
    float t[MAX_IMP];			 //konce èasových intervalù konstantního mg.pole
    float Gx[MAX_IMP],
          Gy[MAX_IMP],
          Gz[MAX_IMP];         //složky gradientù
    float B1[MAX_IMP];         /*amplituda RF pole,které je konstantní v rot.souøadnicích
  					   (tj. je na stejné frekvenci jako rot.souø,která se mùže lišit
                        od larmorovy frekvence dané B0,já tedy v øešení pøedpokládám
                        modulaci komplexní obálky na frekvenci vysílací a pøípadné rozdíly
                        larmorovy frekvence respektuji jako ss. pøíspìvek ke gradientu)*/
    float F1[MAX_IMP];        //frekvence pulsu
    float B0;         //velikost ss magnetického pole urèuje larmorùv kmitoèet
    BYTE  NI,NS;      //poèet impulsù magnetického pole a poøadí snímacího impulsu
    BYTE  Ngy,Ngz;    //poøadí fázovì kódujících impulsù gradientù
    float gy0,gz0;    //pøírùstky gradientù
          } Field;    //prùbìh magnetického pole

struct pulse_1D NewField;

typedef struct {
  float huge ***T1;
  float huge ***T2;
  float huge ***M0;
                } TISSUE;    //pole tkánì

TISSUE Tissue;


double  huge **aImage; //2D pole zobrazovaného obrazu
complex huge ***aCplxImage;//3D pole komplexniho obrazu (po ifft3)
complex huge ***aCplxEnvelope;//3D pole komplexniho obalky NMR signalu

float phase1=0;		       //referenèní fáze pro zobrazení komplexní obálky
float phase2=0;                //referenèní fáze pro zobrazení NMR signálu
 

WORD PosX=0,PosY=0,PosZ=0;  //z-tový index v tìlese

#define Slider MainForm->ScrollBar1
BYTE ActiveView=actNO;      //aktuálnì zobrazovaná distribuce

#define  met32D    0
#define  met33D    1

#define  beg90     0
#define  begIR     1
#define  begRR     2

//------------------------------ default prùbìh magnetického pole ---------------------------------------------
#define  ty  0.05           //délka gradientu Gy
#define  t1  10e-3           //délka budícího impulsu
#define  A90 0.5872e-6     //amplituda 90-stupnoveho radio imp
#define  fres 4.257394727708e+7 //rezonanèní frekvence



float   t[7]={t1,0.05,ty,0.05,t1,0.05,0.05};
float   B1[7]={A90,0.00,0.00,0.00,2*A90,0.0,0.00};
float   F1[7]={fres,0.00,0.00,0.00,fres,0.0,0.00};
float   Gx[7]={0.00,0.00,0.00,0.00,0.00,0.00,0.00};
float   Gy[7]={0.00,0.00,0.00,0.00,0.00,0.00,0.00};
float   Gz[7]={0.00,0.00,0.00,0.00,0.00,0.00,0.00};


void SetField1()
{
 BYTE   i;


 Field.NI =7;
 for (i=0;i<7;i++)
   {
    Field.t[i] = t[i];
    Field.Gx[i]=Gx[i];
    Field.Gy[i]=Gy[i];
    Field.Gz[i]=Gz[i];
    Field.B1[i]=B1[i];
    Field.F1[i]=F1[i];

   }

  Field.B0=1;
  Field.NS=6;
  Field.Ngy=3;
  Field.Ngz=3;

  Field.Gx[Field.NS -1]=2*3.14159265359/(GamaH*Nx*Ts);  //velikost indexového gradientu ve smìru j (x)
  Field.gy0=2*3.14159265359/(GamaH*Ny*ty);  //velikost kroku indexového gradientu ve smìru i (y)
  Field.gz0=2*3.14159265359/(GamaH*Nz*ty);  //velikost kroku indexového gradientu ve smìru i (z)
}

#undef  ty
#undef  t1
#undef  A90
#undef  fres



#endif
