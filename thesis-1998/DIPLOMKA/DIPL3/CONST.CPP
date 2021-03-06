#ifndef _constincluded

  #define _constincluded
  #define huge			//nutno definovat pro C++ Builder,pro BCW odstranit !!
//---------------------------------------------------------------------------
  #include <vcl\vcl.h>
  #include <complex.h>
  #include "alloc_nd.hpp"
  #pragma hdrstop


//-------------------------------zobrazov�n� (vykreslen�)--------------------------------------------
  #define  N_SHADES 128		//po�et odst�n� �ed� pro vykreslov�n�
  #define  MAX_IMP  30      //maxim�ln� po�et impuls� mg.pole
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

//-------------------------------parametry zobrazovac�ho syst�mu a jejich default hodnoty --------
  double   deltaB0=0;          //odchylka ss. pole od hodnoty odpov�daj�c� RF frekvenci
  double   fsample=2e3;        //vzorkovac� frekvence (ob�lky sign�lu) [Hz]
  float    Ts=1e-6;            //vzorkovac� perioda
  WORD     Nx=8,Ny=8,Nz=8;     //rozm�ry t�lesa

  double   HistMin,HistMax;    //minim�ln� a maxim�ln� hodnoty histogramu
  #define  hisLin 0
  #define  hisLog 1
  BYTE     HistType=hisLin;          //typ. p�evodn� charakteristiky
  float    HistLog=2.718281828459;   //z�klad logaritmick� p�evodn� charakteristiky
//-------------------------------fyzik�ln� konstanty--------------------------------------------
  #define  GamaH    2.675e+8  //gyromagnetick� koeficient j�dra vod�ku (protonu)
  #define  Pi  acos(-1)       // 3.142 ...
//-------------------------------default parametry pou�it� zobrazovac� metody--------------------------------------------
  BYTE  Method=0,BegCond=2;     //��sla pou�it� zobrazovac� metody a po�. podm�nek
  BYTE  OldMethod,OldBegCond;  //��sla p�edchoz�  pou�it� zobrazovac� metody a po�. podm�nek
//-------------------------------default parametry testovac�ho t�lesa--------------------------------------------
  #define   temp 310
  #define   b0 1
  #define  Kboltz 1.38e-23 	//Boltzmanova konstanta
  #define  mi 1.4106e-26        //magnetick� moment protonu
  #define  Nprot  6.6887e+28	//densita protonu ve vode [m^(-3)]

  float TestT1a=2.8,TestT2a=0.25,TestM0a=Nprot*mi*tanh(mi*b0/(Kboltz*temp));
  float TestT1b=1.4,TestT2b=0.50,TestM0b=Nprot/2*mi*tanh(mi*b0/(Kboltz*temp));
  WORD  TestNx=8,TestNy=8,TestNz=8;   //rozm�ry testovac�ho t�lesa
  BYTE  TestType=0;                   //typ testovac�ho t�lesa
  #undef  temp
  #undef  b0
  #undef  Kboltz
  #undef  mi
  #undef  Nprot

//-------------------------------default soubor magnetick�ho pole--------------------------------------------
  char  FieldName[255]="standard.mag";
//-------------------------------default hodnota prvn� barvy--------------------------------------------
  BYTE    N_COLORS=10;		//po�et barev syst�mov� palety(==index �ern� barvy po realizaci palety)
//------------------------------ glob�ln� prom�nn� ---------------------------------------------

  BYTE huge **aView;  //pointer to bitmap arrays for bitmap image
  HBITMAP hbmp,hbmppal;
  BYTE    counted[Nchild]={0,0,0,0};

  BYTE aPalette[256][2];
  BITMAP bm;




SPACE ***Mbeg;              //pole po��te�n�ch podm�nek
  
  struct pulse_1D{
    float t[MAX_IMP];			 //konce �asov�ch interval� konstantn�ho mg.pole
    float Gx[MAX_IMP],
          Gy[MAX_IMP],
          Gz[MAX_IMP];         //slo�ky gradient�
    float B1[MAX_IMP];         /*amplituda RF pole,kter� je konstantn� v rot.sou�adnic�ch
  					   (tj. je na stejn� frekvenci jako rot.sou�,kter� se m��e li�it
                        od larmorovy frekvence dan� B0,j� tedy v �e�en� p�edpokl�d�m
                        modulaci komplexn� ob�lky na frekvenci vys�lac� a p��padn� rozd�ly
                        larmorovy frekvence respektuji jako ss. p��sp�vek ke gradientu)*/
    float F1[MAX_IMP];        //frekvence pulsu
    float B0;         //velikost ss magnetick�ho pole ur�uje larmor�v kmito�et
    BYTE  NI,NS;      //po�et impuls� magnetick�ho pole a po�ad� sn�mac�ho impulsu
    BYTE  Ngy,Ngz;    //po�ad� f�zov� k�duj�c�ch impuls� gradient�
    float gy0,gz0;    //p��r�stky gradient�
          } Field;    //pr�b�h magnetick�ho pole

struct pulse_1D NewField;

typedef struct {
  float huge ***T1;
  float huge ***T2;
  float huge ***M0;
                } TISSUE;    //pole tk�n�

TISSUE Tissue;


double  huge **aImage; //2D pole zobrazovan�ho obrazu
complex huge ***aCplxImage;//3D pole komplexniho obrazu (po ifft3)
complex huge ***aCplxEnvelope;//3D pole komplexniho obalky NMR signalu

float phase1=0;		       //referen�n� f�ze pro zobrazen� komplexn� ob�lky
float phase2=0;                //referen�n� f�ze pro zobrazen� NMR sign�lu
 

WORD PosX=0,PosY=0,PosZ=0;  //z-tov� index v t�lese

#define Slider MainForm->ScrollBar1
BYTE ActiveView=actNO;      //aktu�ln� zobrazovan� distribuce

#define  met32D    0
#define  met33D    1

#define  beg90     0
#define  begIR     1
#define  begRR     2

//------------------------------ default pr�b�h magnetick�ho pole ---------------------------------------------
#define  ty  0.05           //d�lka gradientu Gy
#define  t1  10e-3           //d�lka bud�c�ho impulsu
#define  A90 0.5872e-6     //amplituda 90-stupnoveho radio imp
#define  fres 4.257394727708e+7 //rezonan�n� frekvence



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

  Field.Gx[Field.NS -1]=2*3.14159265359/(GamaH*Nx*Ts);  //velikost indexov�ho gradientu ve sm�ru j (x)
  Field.gy0=2*3.14159265359/(GamaH*Ny*ty);  //velikost kroku indexov�ho gradientu ve sm�ru i (y)
  Field.gz0=2*3.14159265359/(GamaH*Nz*ty);  //velikost kroku indexov�ho gradientu ve sm�ru i (z)
}

#undef  ty
#undef  t1
#undef  A90
#undef  fres



#endif
