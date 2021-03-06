#ifndef konstanty
#define konstanty
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
//---------------------------------------------------------------------------
#define  GroupRootKey   "NMR Imaging"
#define  BodyedRootKey  "Bodyed"

#define  LTISSUE 20             //maxim�ln� d�lka  �et�zce n�zvu tk�n�
#define  NViews  1
#define  maxNTissues 200
BYTE     N_COLORS=10;		//po�et barev syst�mov� palety(==index �ern� barvy po realizaci palety)
#define  N_SHADES 128           //po�et odst�n� �edi

#define  Kboltz 1.38e-23 	//Boltzmanova konstanta
#define  mi 1.4106e-26		//magnetick� moment protonu
//#define  Nprot  6.6887e+28	//densita protonu ve vode [m^(-3)]
#define  GamaH    2.675e+8 //gyromagnetick� koeficient j�dra vod�ku (protonu)
//#define Iu  complex(0,1) // imaginarni jednotka
#define Pi  acos(-1)       // 3.142 ...
#define Temp0 273.15       // 0 Celsia v Kelvinech
double B0=1,Temp=37,Freq=GamaH*B0/(2*Pi); //s�la hlavn�ho magnetick�ho pole,teplota tk�n�
WORD Nx=16,Ny=16,Nz=16;          //rozm�ry t�lesa

BYTE  ***aBody;  //pointer na t�leso (max 256 r�zn�ch tk�n�)
float ***aTemp;  //pointer na pole s distribuc� teploty


WORD PosX=0,PosY=0,PosZ=0;  //pozice v t�lese

/*element vyhled�vac� tabulky (z�znam obsahuj�c� informaci o vlastnostech tk�n�
  a o barv� pou�it� k vyobrazen� dan� tk�n�) */
typedef struct {
                char  tissue[LTISSUE];//jm�no tk�n�
                float T1,T2,Nprot;    //parametry tk�n�
                float kT1,kT2;        //teplotn� koeficienty relaxa�n�ch konstant
                BYTE  Red,Green,Blue; //barva

			   } LUELEM;
/*vyhled�vac� tabulka index ozna�uje hodnotu uvedenou v poli aBody
  tj. hodnota LookUp[aBody[k][j][i]) je z�znam o vlastnostech a barv� tk�n�
  na pozici x==i;y==j;z==k)*/
LUELEM LookUp[maxNTissues];


HPALETTE    hpalTissues,hpalShades;
LOGPALETTE *plTissues,*plShades;
BYTE aPalette[256][2];      //pole palety
BYTE aColor[2][2];          //"pole" barvy
unsigned int NRecords;      //po�et z�znam� v datab�zi
unsigned int BcgTissue=0;   //index tk�n� pou�it� jako pozad�
char BcgTissName[LTISSUE];  //jm�no tk�n� pou�it� jako pozad�
BYTE  ActTissue=1;          //index aktu�ln� pou��van� tk�n�
float ActTemp=37;           //teplota n�stroj� -hodnota aktu�ln� pou��van� teploty

HBITMAP hbmp;
unsigned char **aView;
TScrollBar    *Slider;

double HistMin,HistMax;   //maxim�ln� a minim�ln� hodnota v aktu�ln�m histogramu

//--------------------------------aktivn� zobrazen�-----------------------------
#define actTis 0         //te
#define actTem 1
#define actPal 2
BYTE ActiveView=actTis; //aktivn� zobrazen�

//--------------------------------aktivn� n�stroj-----------------------------
#define atlNon  0       //��dn�
#define atlPoi  1       //bod
#define atlSph  2       //koule
#define atlCub  3       //krychle
#define atlRec  4       //kv�dr
#define atlEll  5       //elipsoid
#define atlCyl  6       //elipsoid

BYTE ActiveTool=atlNon; //aktivn� zobrazen�


typedef struct{
                float x,y,z; //sou�adnice bodu
	      } SPACE;


/*nastaven� jednotliv�ch n�stroj�*/
//-------------------------------KOULE--------------------------------------------------------------
float t_Sphere_Rad=10;    //polom�r koule
//-------------------------------ELIPSOID--------------------------------------------------------------
float t_Ellipsoid_RadX=10;    //polom�r X
float t_Ellipsoid_RadY=12;    //polom�r Y
float t_Ellipsoid_RadZ=16;    //polom�r Z
float t_Ellipsoid_Alpha=0;    //�hel alfa
float t_Ellipsoid_Beta=0;     //�hel beta
float t_Ellipsoid_Gama=0;     //�hel gama

//-------------------------------KV�DR--------------------------------------------------------------
float t_Rectangular_a=10;    //strana a
float t_Rectangular_b=5;     //strana b
float t_Rectangular_c=3;     //strana c
float t_Rectangular_Alpha=0;   //�hel alfa
float t_Rectangular_Beta=0;     //�hel beta
float t_Rectangular_Gama=0;     //�hel gama
//-------------------------------KRYCHLE--------------------------------------------------------------
float t_Cube_a=10;      //strana krychle
float t_Cube_Alpha=0;   //�hel alfa
float t_Cube_Beta=0;    //�hel beta
float t_Cube_Gama=0;    //�hel gama

//-------------------------------V�LEC--------------------------------------------------------------
float t_Cylinder_r=10;      //polom�r v�lce
float t_Cylinder_l=5;       //d�lka v�lce b
float t_Cylinder_Alpha=0;   //�hel alfa
float t_Cylinder_Beta=0;    //�hel beta
float t_Cylinder_Gama=0;    //�hel gama

//-------------------------------------koeficienty transforma�n� matice -----------------------------
float s11,s12,s13;
float s21,s22,s23;
float s31,s32,s33;

char savemsg[100]="Chvilku strpen� ukl�d�m soubor";
char openmsg[100]="Chvilku strpen� otev�r�m soubor";

#endif
