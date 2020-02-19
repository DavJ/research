#ifndef _imageprocessor
#define _imageprocessor
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop


#include <values.h>
#include <stdlib.h>
#include <math.h>
#include "allocpal.cpp"
#include "Const_BE.cpp"

#include "undo.cpp"
//---------------------------------------------------------------------------
int GetIndex(char *ret)
{
 for (int i=0;i<256;i++)
   if (stricmp(LookUp[i].tissue,ret)==0) return (i);
 return (-1); //nebyl nalezen identický øetìzec
}



//vypocet palety cb. obrazu s n_grays odstiny sedi

HPALETTE Shades(BYTE n_grays)
{
  HPALETTE Palette;  //pomocna promenna
  BYTE i,k;
  LOGPALETTE* plgpl;

plgpl=(LOGPALETTE*)LocalAlloc(LPTR,sizeof(LOGPALETTE)+n_grays*sizeof(PALETTEENTRY));
plgpl->palNumEntries = n_grays;
plgpl->palVersion = 0x300;

k=(BYTE)255/(n_grays-1);/*nasobny koeficient pro maximalni kontrast
	     		     musi byt celistve cislo pro rovnomernou
                             stupnici sedi*/

    for (i = 0; i<(n_grays);i++) {
      plgpl->palPalEntry[i].peRed =k*i;
      plgpl->palPalEntry[i].peGreen =k*i;
      plgpl->palPalEntry[i].peBlue = k*i;
      plgpl->palPalEntry[i].peFlags =PC_NOCOLLAPSE;//NULL;
      };

    Palette = CreatePalette(plgpl);
    LocalFree((HLOCAL) plgpl);
    return  Palette;
}



void Histogram(float huge **in,BYTE huge **out,unsigned int Ny,unsigned int Nx)
{
  unsigned int i,j;
  BYTE Black;
  double delt,smer;
  HistMin=MAXDOUBLE;			//inicializace maximalni a minimalni hodnoty
  HistMax=-MAXDOUBLE;

//urceni parametru linearni prevodni charakteristiky pro max. kontrast
  for (i=0;i<Ny;i++)
    for (j=0;j<Nx;j++)
    {
      if (in[i][j]<HistMin) HistMin=in[i][j];
      if (in[i][j]>HistMax) HistMax=in[i][j];
    }

   delt=HistMax-HistMin;
   if (delt==0) {smer=0;HistMin=0;} //smernice ;1 da stejne 0;
   								//pozor HistMin by jinak bylo plus nekonecno ->preteceni
    else smer=(N_SHADES-1)/delt;

   Black=N_COLORS;//index cerne barvy v palete definovan v const.cpp

 //zmena histogramu a prevedeni double -> BYTE
  for (i=0;i<Ny;i++)
    for (j=0;j<Nx;j++)
      out[i][j]=((in[i][j]-HistMin)*smer)+Black;
}

/*posune hodnoty 2D pole o N_COLORS kvùli správnému zobrazení*/
void ShiftColors(BYTE huge **in,BYTE huge **out,unsigned int Ny,unsigned int Nx)
{
  WORD i,j;
  for (i=0;i<Ny;i++)
    for (j=0;j<Nx;j++)
      out[i][j]=in[i][j]+N_COLORS;
}




/*vrátí požadované údaje T1,T2 a Nprot z n-tého záznamu
 VSTUP  ukazatele na jednotlivé databázove položky typu
        TStringField
 VÝSTUP element tabulky elem
*/
unsigned int GetRecord(unsigned int n,
					  TTable *Table,
                      TStringField *TableTKAN,
                      TStringField *TableT1,
                      TStringField *TableT2,
                      TStringField *TableNPROT,
                      TStringField *TableKT1,
                      TStringField *TableKT2,
                      TStringField *TableRED,
                      TStringField *TableGREEN,
	              TStringField *TableBLUE,
                      LUELEM &elem)
{
 unsigned int i,j;
 Table->DisableControls(); //zakázání zmìn na obrazovce

  i=0;
  while(!Table->Bof)  //urèí poøadí aktuálního záznamu a nastaví první záznam
   {
     i++;
     Table->Prior();//kurzor na další záznam
   }

  for (j=0;j<n;j++)
     Table->Next();


  sprintf(elem.tissue,"%s",TableTKAN->AsString.c_str());
  //error-pozor nutno dopoèítat podle aktuální frekvence NMR! T1=f(f)
  elem.T1=TableT1->AsFloat;
  elem.T2=TableT2->AsFloat;
  elem.Nprot=TableNPROT->AsFloat;
  elem.kT1=TableKT1->AsFloat;
  elem.kT2=TableKT2->AsFloat;
  elem.Red=TableRED->AsFloat;
  elem.Green=TableGREEN->AsFloat;
  elem.Blue=TableBLUE->AsFloat;


  Table->First();//nastavení kurzoru na první záznam v databázi
    for (j=0;j<i;j++) //vrácení kursoru na pùvodní posici
     Table->Next();

  Table->EnableControls(); //povolení zmìn na obrazovce

  return(1);
}


unsigned int GetNRecords(TTable *Table)
{
  unsigned int i;
  Table->DisableControls(); // Speed up processing, prevent screen flicker
  Table->First();//nastavení kurzoru na první záznam v databázi
  i=0;
  while(!Table->Eof)  //urèí poèet záznamù v databázi
   {
     i++;
     Table->Next();//kurzor na další záznam
   }
  Table->EnableControls(); // Speed up processing, prevent screen flicker
  //Zde má  být varování pro i>maxNTissues !!! (o ignorování zbylých tkání0
  if (i>maxNTissues) i=maxNTissues; //ignorování tkání pøesahující povolený poèet

  return i;
}
//nastavení hodnot vyhledávací tabulky podle databáze
void SetLUTable(  TTable *Table,
                  TStringField *TableTKAN,
                  TStringField *TableT1,
                  TStringField *TableT2,
                  TStringField *TableNPROT,
                  TStringField *TableKT1,
                  TStringField *TableKT2,
                  TStringField *TableRED,
                  TStringField *TableGREEN,
	          TStringField *TableBLUE )

{
 unsigned int i;
 for (i=0;i<NRecords;i++)
   GetRecord(i,Table,TableTKAN,TableT1,TableT2,TableNPROT,TableKT1,TableKT2,TableRED,TableGREEN,TableBLUE,LookUp[i]);

}



HPALETTE TissueColors(LOGPALETTE *plgpl)
{
  HPALETTE Palette;  //pomocna promenna
  unsigned int i;

  for (i=0;i<plgpl->palNumEntries;i++) //nastaví barevné složky podle databáze
   {
     plgpl->palPalEntry[i].peRed = LookUp[i].Red;
     plgpl->palPalEntry[i].peGreen = LookUp[i].Green;
     plgpl->palPalEntry[i].peBlue = LookUp[i].Blue;
     plgpl->palPalEntry[i].peFlags =PC_NOCOLLAPSE;//NULL;
   }


  Palette = CreatePalette(plgpl);
  return  Palette;
}

//najde první index v logické paletì plgpl odpovídají požadované barvì
int  ColorToIndex(LOGPALETTE *plgpl,TColor Color)
{
  unsigned int Red,Green,Blue;
  unsigned int i;

  Red  =(0x000000FF&Color);
  Green=(0x0000FF00&Color)>>8;
  Blue =(0x00FF0000&Color)>>16;

  for (i=0;i<plgpl->palNumEntries;i++) //nastaví barevné složky podle databáze
   {
     if (plgpl->palPalEntry[i].peRed ==Red)
      if (plgpl->palPalEntry[i].peGreen ==Green)
       if (plgpl->palPalEntry[i].peBlue ==Blue)  return(i);
  //funkce vrátí hodnotu i jsou-li všechny tøi složky barvy rovny požadovaným
   }
 return(-1);      //barva nenalezena
}


void RefreshImage(TImage *Image,BYTE active)
{
  ActiveView=active;
  switch (ActiveView) {
    case actTis:   ShiftColors(aBody[PosZ],aView,Ny,Nx);
                   hbmp=CreateBitmap(Nx,Ny, 1, 8,aView[0]); //musí být po každé zmìnì pole aView jinak se nevykreslí
  		   Image->Picture->Bitmap->Handle =hbmp;
 		   if (Image->Picture->Bitmap->Handle == NULL) MessageBox(NULL,"Nepodaøilo  se vytvoøit bitmapu !","message",MB_OK);
                   Application->ProcessMessages();
    		   break;
    case actTem:   Histogram(aTemp[PosZ],aView,Ny,Nx);
                   hbmp=CreateBitmap(Nx,Ny, 1, 8,aView[0]); //musí být po každé zmìnì pole aView jinak se nevykreslí
  		   Image->Picture->Bitmap->Handle =hbmp;
 		   if (Image->Picture->Bitmap->Handle == NULL) MessageBox(NULL,"Nepodaøilo  se vytvoøit bitmapu !","message",MB_OK);
                   Application->ProcessMessages();
    		   break;
    case actPal:   hbmp=CreateBitmap(2,256, 1, 8,aPalette[0]); //musí být po každé zmìnì pole aView jinak se nevykreslí
  		   Image->Picture->Bitmap->Handle =hbmp;
 		   if (Image->Picture->Bitmap->Handle == NULL) MessageBox(NULL,"Nepodaøilo  se vytvoøit bitmapu !","message",MB_OK);
                   Application->ProcessMessages();
                   break;
                      }
 }




//--------------------------kreslení----------------------------------
void DrawPoint()
{
 EXCISION SavePoint;
 BYTE a;
 SavePoint.xpos=PosX;SavePoint.ypos=PosY;SavePoint.zpos=PosZ; //zapamatování pozice bodu
 SavePoint.Nx=1;SavePoint.Ny=1;SavePoint.Nz=1;                //výsek 1x1x1
 SavePoint.Body=ByteAlloc_3D(1,1,1);
 SavePoint.Temp=FloatAlloc_3D(1,1,1);
 SavePoint.Body[0][0][0]=aBody[PosZ][PosY][PosX];    //zapamatování tkánì
 SavePoint.Temp[0][0][0]=aTemp[PosZ][PosY][PosX];    //zapamatování teploty
 AddBackStep(SavePoint);				      //pøidání zpìtného kroku

 aBody[PosZ][PosY][PosX]=ActTissue;
 aTemp[PosZ][PosY][PosX]=ActTemp;
}

//--------------------------- koule ------------------------------------

void DrawSphere()
{
 EXCISION excision;
 WORD Rmax=ceil(abs(t_Sphere_Rad));
 WORD k,j,i;
 float x,y,z;
 //alokace výøezu
 AllocExcision(PosX-Rmax,PosY-Rmax,PosZ-Rmax,PosX+Rmax,PosY+Rmax,PosZ+Rmax,&excision);

     for (i=0;i<excision.Nx;i++)
       {
        x=i+excision.xpos;
        for (j=0;j<excision.Ny;j++)
          {
	   y=j+excision.ypos;
           for (k=0;k<excision.Nz;k++)
             {
              z=k+excision.zpos;
              if (pow((x-PosX),2)+pow((y-PosY),2)+pow((z-PosZ),2)<pow((t_Sphere_Rad),2))
              	    excision.Body[k][j][i]=true;  //bod leží uvnitø koule
               else excision.Body[k][j][i]=false; //bod leží vnì koule
             }
          }
        }

 CopyExcision(&excision);
 AddBackStep(excision);				      //pøidání zpìtného kroku
}
//--------------------------- rotace souøadnic ----------------------------------
/* vypoèítá koeficienty transformaèní matice pro rotaci souøadné soustavy o úhly a,b,c
   kolem os x,y,z */
void SetRotationMatrix(float alpha,float beta,float gama)
{
  float a=alpha/180.0*Pi;
  float b= beta/180.0*Pi;
  float c= gama/180.0*Pi;


  s11= cos(a)*cos(b);
  s12= sin(a)*cos(b);
  s13=-sin(b);

  s21=-sin(a)*cos(c)+cos(a)*sin(b)*sin(c);
  s22= cos(a)*cos(c)+sin(a)*sin(b)*sin(c);
  s23= cos(b)*sin(c);

  s31= sin(a)*sin(c)+cos(a)*sin(b)*cos(c);
  s32=-cos(a)*sin(c)+sin(a)*sin(b)*cos(c);
  s33= cos(b)*cos(c);

  /*s31= sin(a)*sin(c)-sin(a)*sin(b)*cos(c);
  s32=-cos(a)*sin(c)+cos(a)*sin(b)*cos(c);
  s33= cos(b)*cos(c); */

}

SPACE Transformation(SPACE Sour)
{
  SPACE  Rot;
  Rot.x=s11*Sour.x+s12*Sour.y+s13*Sour.z;
  Rot.y=s21*Sour.x+s22*Sour.y+s23*Sour.z;
  Rot.z=s31*Sour.x+s32*Sour.y+s33*Sour.z;
  return (Rot);
}
//--------------------------- elipsoid ------------------------------------
void DrawEllipsoid()
{
 EXCISION excision;
 WORD Rmax=ceil(max(abs(t_Ellipsoid_RadX),max(abs(t_Ellipsoid_RadY),abs(t_Ellipsoid_RadZ))));
 WORD k,j,i;
 SPACE stat,rot;

 SetRotationMatrix(t_Ellipsoid_Alpha,t_Ellipsoid_Beta,t_Ellipsoid_Gama);
 //alokace výøezu
 AllocExcision(PosX-Rmax,PosY-Rmax,PosZ-Rmax,PosX+Rmax,PosY+Rmax,PosZ+Rmax,&excision);

     for (i=0;i<excision.Nx;i++)
       {
        stat.x=i+excision.xpos-PosX;
        for (j=0;j<excision.Ny;j++)
          {
	   stat.y=j+excision.ypos-PosY;
           for (k=0;k<excision.Nz;k++)
             {
              stat.z=k+excision.zpos-PosZ;
              rot=Transformation(stat);
              if (pow(rot.x/t_Ellipsoid_RadX,2)+pow(rot.y/t_Ellipsoid_RadY,2)+pow(rot.z/t_Ellipsoid_RadZ,2)<1)
              	    excision.Body[k][j][i]=true;  //bod leží uvnitø elipsoidu
               else excision.Body[k][j][i]=false; //bod leží vnì elipsoidu
             }
          }
        }

 CopyExcision(&excision);
 AddBackStep(excision);				      //pøidání zpìtného kroku
}

//--------------------------- kvádr -----------------------------------------
void DrawRectangular()
{
 EXCISION excision;
 WORD Rmax=ceil(sqrt(pow(t_Rectangular_a,2)+pow(t_Rectangular_b,2)+pow(t_Rectangular_c,2)));
 WORD k,j,i;
 SPACE stat,rot;

 SetRotationMatrix(t_Rectangular_Alpha,t_Rectangular_Beta,t_Rectangular_Gama);
 //alokace výøezu
 AllocExcision(PosX-Rmax,PosY-Rmax,PosZ-Rmax,PosX+Rmax,PosY+Rmax,PosZ+Rmax,&excision);

     for (i=0;i<excision.Nx;i++)
       {
        stat.x=i+excision.xpos-PosX;
        for (j=0;j<excision.Ny;j++)
          {
	   stat.y=j+excision.ypos-PosY;
           for (k=0;k<excision.Nz;k++)
             {
              stat.z=k+excision.zpos-PosZ;
              rot=Transformation(stat);
              if ((abs(rot.x)<t_Rectangular_a/2)&&(abs(rot.y)<t_Rectangular_b/2)&&(abs(rot.z)<t_Rectangular_c/2))
              	    excision.Body[k][j][i]=true;  //bod leží uvnitø kvádru
               else excision.Body[k][j][i]=false; //bod leží vnì kvádru
             }
          }
        }

 CopyExcision(&excision);
 AddBackStep(excision);				      //pøidání zpìtného kroku
}
//--------------------------- krychle -----------------------------------------
void DrawCube()
{
 EXCISION excision;
 WORD Rmax=ceil(sqrt(3*pow(t_Cube_a,2)));
 WORD k,j,i;
 SPACE stat,rot;

 SetRotationMatrix(t_Cube_Alpha,t_Cube_Beta,t_Cube_Gama);
 //alokace výøezu
 AllocExcision(PosX-Rmax,PosY-Rmax,PosZ-Rmax,PosX+Rmax,PosY+Rmax,PosZ+Rmax,&excision);

     for (i=0;i<excision.Nx;i++)
       {
        stat.x=i+excision.xpos-PosX;
        for (j=0;j<excision.Ny;j++)
          {
	   stat.y=j+excision.ypos-PosY;
           for (k=0;k<excision.Nz;k++)
             {
              stat.z=k+excision.zpos-PosZ;
              rot=Transformation(stat);
              if ((abs(rot.x)<t_Cube_a/2)&&(abs(rot.y)<t_Cube_a/2)&&(abs(rot.z)<t_Cube_a/2))
              	    excision.Body[k][j][i]=true;  //bod leží uvnitø kvádru
               else excision.Body[k][j][i]=false; //bod leží vnì kvádru
             }
          }
        }

 CopyExcision(&excision);
 AddBackStep(excision);				      //pøidání zpìtného kroku
}
//--------------------------- válec -----------------------------------------
void DrawCylinder()
{
 EXCISION excision;
 WORD Rmax=ceil(sqrt(pow(t_Cylinder_r,2)+pow(t_Cylinder_l,2)));
 WORD k,j,i;
 SPACE stat,rot;

 SetRotationMatrix(t_Cylinder_Alpha,t_Cylinder_Beta,t_Cylinder_Gama);
 //alokace výøezu
 AllocExcision(PosX-Rmax,PosY-Rmax,PosZ-Rmax,PosX+Rmax,PosY+Rmax,PosZ+Rmax,&excision);

     for (i=0;i<excision.Nx;i++)
       {
        stat.x=i+excision.xpos-PosX;
        for (j=0;j<excision.Ny;j++)
          {
	   stat.y=j+excision.ypos-PosY;
           for (k=0;k<excision.Nz;k++)
             {
              stat.z=k+excision.zpos-PosZ;
              rot=Transformation(stat);
              if ((pow(rot.x,2)+pow(rot.y,2)<pow(t_Cylinder_r,2))&&(abs(rot.z)<t_Cylinder_l/2))
              	    excision.Body[k][j][i]=true;  //bod leží uvnitø kvádru
               else excision.Body[k][j][i]=false; //bod leží vnì kvádru
             }
          }
        }

 CopyExcision(&excision);
 AddBackStep(excision);				      //pøidání zpìtného kroku
}
#endif
