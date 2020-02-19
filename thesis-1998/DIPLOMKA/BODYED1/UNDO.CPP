#ifndef _backsteps
#define _backsteps
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Alloc_nd.hpp"
#include "Const_BE.cpp"
//---------------------------------------------------------------------------
#define maxNBackSteps 10  //maximální poèet zpìtných krokù
//struktura výøez  a také element tabulky zpìtných krokù
typedef struct{
                WORD Nx,Ny,Nz; //rozmìry výøezu (zapamatované oblasti)
                WORD xpos,ypos,zpos; //poloha výøezu (zapamatované oblasti) odpovídá indexu [0][0][0] výøezu
                float ***Temp; //ukazatel na pole zapamatované distribuce teploty
                BYTE  ***Body; //ukazatel na pole zapamatované distribuce tkánì
                               //nebo obsahuje hodnoty false resp. true pro geometrickou reprezentaci tvaru objektu
	      } EXCISION;

EXCISION BackSteps[maxNBackSteps];

BYTE NBackSteps=0; //skuteèný poèet zaznamenaných zpìtných krokù


//alokuje pamì pro výøez s hranicemi viz. parametry (vèetnì) s ohledem na hranice tìlesa  a nastaví skuteèné rozmìry a pozici výøezu
//--------------------------- alokace pamìti pro výøez -----------------
/*alokace výøezu s respektováním mezí tìlesa
  vrací pointer na výøezová pole s distribucí tkánì bd a teploty tm
  a velikost výøezu (Nvx x Nvy x Nvz)
  */
void AllocExcision(int xmin,int ymin,int zmin,int xmax,int ymax,int zmax,EXCISION *excis)
{
  //nastavení poèátku výøezu
  excis->xpos=max(0,xmin);
  excis->ypos=max(0,ymin);
  excis->zpos=max(0,zmin);
  //nastavení rozmìrù výøezu
  excis->Nx=min((int)Nx-1,xmax)-max(0,xmin)+1; //+1  nebo chci mít zahrnuto ve ve výøezu jak xmin tak xmax
  excis->Ny=min((int)Ny-1,ymax)-max(0,ymin)+1; //Nx-1 je maximální horní mez pro x,0 je minimánlí spodní mez
  excis->Nz=min((int)Nz-1,zmax)-max(0,zmin)+1;

  //alokace pamìti pro teplotní a tkáòovou distribuci výøezu
  excis->Body=ByteAlloc_3D(excis->Nz,excis->Ny,excis->Nx);
  excis->Temp=FloatAlloc_3D(excis->Nz,excis->Ny,excis->Nx);
}


//pøekopíruje objekt definovaný ve výøezu hodnotami true do tìlesa aBody a aTemp

/*pøekopíruje výøez do aBody,aTemp ,tak že všechny hodnoty true nahradí indexem
 aktuální tkánì a aktuální teplotou,pøitom jsou do celého výøezu(i tam kde
 byly hodnoty false) uloženy hodnoty z polí aBody,aTemp-tím je umožnìno pamatování
 zmìn */


void CopyExcision(EXCISION *excision)
{
  WORD i,j,k;
      for (i=0;i<excision->Nx;i++)
       for (j=0;j<excision->Ny;j++)
         for (k=0;k<excision->Nz;k++)
           {
            if (excision->Body[k][j][i])  //true vnitøek tìlesa
               {
                excision->Body[k][j][i]=aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                excision->Temp[k][j][i]=aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos]=ActTissue;
                aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos]=ActTemp;
               }
            else     //false vnìjšek tìlesa
               {
                excision->Body[k][j][i]=aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                excision->Temp[k][j][i]=aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos];
               }
           }
}


//pøidá zpìtný krok do tabulky zpìtných krokù  (zaøadí výøez do bufferu)
void AddBackStep(EXCISION Step)
{
 BYTE i;
  for (i=maxNBackSteps-1;i>0;i--) BackSteps[i]=BackSteps[i-1];
  if  (NBackSteps<maxNBackSteps) NBackSteps++;
  //uložení nejnovìjšího zpìtného kroku na pozici 0
  BackSteps[0]=Step;
};

//zruší pøedchozí zmìnu  (vrátí výøez z bufferu do tìlesa)
void Undo()
{
  WORD i,j,k;

  if  (NBackSteps>0) //je-li zaznamenán zpìtný krok
   {
     for (i=0;i<BackSteps[0].Nx;i++)
       for (j=0;j<BackSteps[0].Ny;j++)
         for (k=0;k<BackSteps[0].Nz;k++)
           {
            //vrácení zapamatovaného výseku do polí aBody,aTemp
            aBody[k+BackSteps[0].zpos][j+BackSteps[0].ypos][i+BackSteps[0].xpos]=BackSteps[0].Body[k][j][i];
            aTemp[k+BackSteps[0].zpos][j+BackSteps[0].ypos][i+BackSteps[0].xpos]=BackSteps[0].Temp[k][j][i];
           }
      //dealokace polí výsekù
      ByteDealloc_3D(BackSteps[0].Body,BackSteps[0].Nz);
      FloatDealloc_3D(BackSteps[0].Temp,BackSteps[0].Nz);

      NBackSteps--;

      for (i=0;i<NBackSteps;i++) BackSteps[i]=BackSteps[i+1];

   }

};

//vymaže zpìtné kroky z pamìti  (dealokuje nclear nejstarších výøezù z pamìti)
void ClearUndo(BYTE nclear)
{
  int n,backsteps=NBackSteps;
  for (n=backsteps-1;n>backsteps-1-nclear;n--)
    {
      //dealokace polí výsekù
      ByteDealloc_3D(BackSteps[n].Body,BackSteps[n].Nz);
      FloatDealloc_3D(BackSteps[n].Temp,BackSteps[n].Nz);
      NBackSteps--;
    }
};


#endif