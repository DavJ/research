#ifndef konstanty
#define konstanty
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
//---------------------------------------------------------------------------
#define  GroupRootKey   "NMR Imaging"
#define  BodyedRootKey  "Bodyed"

#define  LTISSUE 20             //maximální délka  øetìzce názvu tkánì
#define  NViews  1
#define  maxNTissues 200
BYTE     N_COLORS=10;		//poèet barev systémové palety(==index èerné barvy po realizaci palety)
#define  N_SHADES 128           //poèet odstínù šedi

#define  Kboltz 1.38e-23 	//Boltzmanova konstanta
#define  mi 1.4106e-26		//magnetický moment protonu
//#define  Nprot  6.6887e+28	//densita protonu ve vode [m^(-3)]
#define  GamaH    2.675e+8 //gyromagnetický koeficient jádra vodíku (protonu)
//#define Iu  complex(0,1) // imaginarni jednotka
#define Pi  acos(-1)       // 3.142 ...
#define Temp0 273.15       // 0 Celsia v Kelvinech
double B0=1,Temp=37,Freq=GamaH*B0/(2*Pi); //síla hlavního magnetického pole,teplota tkánì
WORD Nx=16,Ny=16,Nz=16;          //rozmìry tìlesa

BYTE  ***aBody;  //pointer na tìleso (max 256 rùzných tkání)
float ***aTemp;  //pointer na pole s distribucí teploty


WORD PosX=0,PosY=0,PosZ=0;  //pozice v tìlese

/*element vyhledávací tabulky (záznam obsahující informaci o vlastnostech tkánì
  a o barvì použité k vyobrazení dané tkánì) */
typedef struct {
                char  tissue[LTISSUE];//jméno tkánì
                float T1,T2,Nprot;    //parametry tkánì
                float kT1,kT2;        //teplotní koeficienty relaxaèních konstant
                BYTE  Red,Green,Blue; //barva

			   } LUELEM;
/*vyhledávací tabulka index oznaèuje hodnotu uvedenou v poli aBody
  tj. hodnota LookUp[aBody[k][j][i]) je záznam o vlastnostech a barvì tkánì
  na pozici x==i;y==j;z==k)*/
LUELEM LookUp[maxNTissues];


HPALETTE    hpalTissues,hpalShades;
LOGPALETTE *plTissues,*plShades;
BYTE aPalette[256][2];      //pole palety
BYTE aColor[2][2];          //"pole" barvy
unsigned int NRecords;      //poèet záznamù v databázi
unsigned int BcgTissue=0;   //index tkánì použité jako pozadí
char BcgTissName[LTISSUE];  //jméno tkánì použité jako pozadí
BYTE  ActTissue=1;          //index aktuálnì používané tkánì
float ActTemp=37;           //teplota nástrojù -hodnota aktuálnì používané teploty

HBITMAP hbmp;
unsigned char **aView;
TScrollBar    *Slider;

double HistMin,HistMax;   //maximální a minimální hodnota v aktuálním histogramu

//--------------------------------aktivní zobrazení-----------------------------
#define actTis 0         //te
#define actTem 1
#define actPal 2
BYTE ActiveView=actTis; //aktivní zobrazení

//--------------------------------aktivní nástroj-----------------------------
#define atlNon  0       //žádný
#define atlPoi  1       //bod
#define atlSph  2       //koule
#define atlCub  3       //krychle
#define atlRec  4       //kvádr
#define atlEll  5       //elipsoid
#define atlCyl  6       //elipsoid

BYTE ActiveTool=atlNon; //aktivní zobrazení


typedef struct{
                float x,y,z; //souøadnice bodu
	      } SPACE;


/*nastavení jednotlivých nástrojù*/
//-------------------------------KOULE--------------------------------------------------------------
float t_Sphere_Rad=10;    //polomìr koule
//-------------------------------ELIPSOID--------------------------------------------------------------
float t_Ellipsoid_RadX=10;    //polomìr X
float t_Ellipsoid_RadY=12;    //polomìr Y
float t_Ellipsoid_RadZ=16;    //polomìr Z
float t_Ellipsoid_Alpha=0;    //úhel alfa
float t_Ellipsoid_Beta=0;     //úhel beta
float t_Ellipsoid_Gama=0;     //úhel gama

//-------------------------------KVÁDR--------------------------------------------------------------
float t_Rectangular_a=10;    //strana a
float t_Rectangular_b=5;     //strana b
float t_Rectangular_c=3;     //strana c
float t_Rectangular_Alpha=0;   //úhel alfa
float t_Rectangular_Beta=0;     //úhel beta
float t_Rectangular_Gama=0;     //úhel gama
//-------------------------------KRYCHLE--------------------------------------------------------------
float t_Cube_a=10;      //strana krychle
float t_Cube_Alpha=0;   //úhel alfa
float t_Cube_Beta=0;    //úhel beta
float t_Cube_Gama=0;    //úhel gama

//-------------------------------VÁLEC--------------------------------------------------------------
float t_Cylinder_r=10;      //polomìr válce
float t_Cylinder_l=5;       //délka válce b
float t_Cylinder_Alpha=0;   //úhel alfa
float t_Cylinder_Beta=0;    //úhel beta
float t_Cylinder_Gama=0;    //úhel gama

//-------------------------------------koeficienty transformaèní matice -----------------------------
float s11,s12,s13;
float s21,s22,s23;
float s31,s32,s33;

char savemsg[100]="Chvilku strpení ukládám soubor";
char openmsg[100]="Chvilku strpení otevírám soubor";

#endif
