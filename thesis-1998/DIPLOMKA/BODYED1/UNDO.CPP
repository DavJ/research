#ifndef _backsteps
#define _backsteps
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Alloc_nd.hpp"
#include "Const_BE.cpp"
//---------------------------------------------------------------------------
#define maxNBackSteps 10  //maxim�ln� po�et zp�tn�ch krok�
//struktura v��ez  a tak� element tabulky zp�tn�ch krok�
typedef struct{
                WORD Nx,Ny,Nz; //rozm�ry v��ezu (zapamatovan� oblasti)
                WORD xpos,ypos,zpos; //poloha v��ezu (zapamatovan� oblasti) odpov�d� indexu [0][0][0] v��ezu
                float ***Temp; //ukazatel na pole zapamatovan� distribuce teploty
                BYTE  ***Body; //ukazatel na pole zapamatovan� distribuce tk�n�
                               //nebo obsahuje hodnoty false resp. true pro geometrickou reprezentaci tvaru objektu
	      } EXCISION;

EXCISION BackSteps[maxNBackSteps];

BYTE NBackSteps=0; //skute�n� po�et zaznamenan�ch zp�tn�ch krok�


//alokuje pam� pro v��ez s hranicemi viz. parametry (v�etn�) s ohledem na hranice t�lesa  a nastav� skute�n� rozm�ry a pozici v��ezu
//--------------------------- alokace pam�ti pro v��ez -----------------
/*alokace v��ezu s respektov�n�m mez� t�lesa
  vrac� pointer na v��ezov� pole s distribuc� tk�n� bd a teploty tm
  a velikost v��ezu (Nvx x Nvy x Nvz)
  */
void AllocExcision(int xmin,int ymin,int zmin,int xmax,int ymax,int zmax,EXCISION *excis)
{
  //nastaven� po��tku v��ezu
  excis->xpos=max(0,xmin);
  excis->ypos=max(0,ymin);
  excis->zpos=max(0,zmin);
  //nastaven� rozm�r� v��ezu
  excis->Nx=min((int)Nx-1,xmax)-max(0,xmin)+1; //+1  nebo� chci m�t zahrnuto ve ve v��ezu jak xmin tak xmax
  excis->Ny=min((int)Ny-1,ymax)-max(0,ymin)+1; //Nx-1 je maxim�ln� horn� mez pro x,0 je minim�nl� spodn� mez
  excis->Nz=min((int)Nz-1,zmax)-max(0,zmin)+1;

  //alokace pam�ti pro teplotn� a tk��ovou distribuci v��ezu
  excis->Body=ByteAlloc_3D(excis->Nz,excis->Ny,excis->Nx);
  excis->Temp=FloatAlloc_3D(excis->Nz,excis->Ny,excis->Nx);
}


//p�ekop�ruje objekt definovan� ve v��ezu hodnotami true do t�lesa aBody a aTemp

/*p�ekop�ruje v��ez do aBody,aTemp ,tak �e v�echny hodnoty true nahrad� indexem
 aktu�ln� tk�n� a aktu�ln� teplotou,p�itom jsou do cel�ho v��ezu(i tam kde
 byly hodnoty false) ulo�eny hodnoty z pol� aBody,aTemp-t�m je umo�n�no pamatov�n�
 zm�n */


void CopyExcision(EXCISION *excision)
{
  WORD i,j,k;
      for (i=0;i<excision->Nx;i++)
       for (j=0;j<excision->Ny;j++)
         for (k=0;k<excision->Nz;k++)
           {
            if (excision->Body[k][j][i])  //true vnit�ek t�lesa
               {
                excision->Body[k][j][i]=aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                excision->Temp[k][j][i]=aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos]=ActTissue;
                aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos]=ActTemp;
               }
            else     //false vn�j�ek t�lesa
               {
                excision->Body[k][j][i]=aBody[k+excision->zpos][j+excision->ypos][i+excision->xpos];
                excision->Temp[k][j][i]=aTemp[k+excision->zpos][j+excision->ypos][i+excision->xpos];
               }
           }
}


//p�id� zp�tn� krok do tabulky zp�tn�ch krok�  (za�ad� v��ez do bufferu)
void AddBackStep(EXCISION Step)
{
 BYTE i;
  for (i=maxNBackSteps-1;i>0;i--) BackSteps[i]=BackSteps[i-1];
  if  (NBackSteps<maxNBackSteps) NBackSteps++;
  //ulo�en� nejnov�j��ho zp�tn�ho kroku na pozici 0
  BackSteps[0]=Step;
};

//zru�� p�edchoz� zm�nu  (vr�t� v��ez z bufferu do t�lesa)
void Undo()
{
  WORD i,j,k;

  if  (NBackSteps>0) //je-li zaznamen�n zp�tn� krok
   {
     for (i=0;i<BackSteps[0].Nx;i++)
       for (j=0;j<BackSteps[0].Ny;j++)
         for (k=0;k<BackSteps[0].Nz;k++)
           {
            //vr�cen� zapamatovan�ho v�seku do pol� aBody,aTemp
            aBody[k+BackSteps[0].zpos][j+BackSteps[0].ypos][i+BackSteps[0].xpos]=BackSteps[0].Body[k][j][i];
            aTemp[k+BackSteps[0].zpos][j+BackSteps[0].ypos][i+BackSteps[0].xpos]=BackSteps[0].Temp[k][j][i];
           }
      //dealokace pol� v�sek�
      ByteDealloc_3D(BackSteps[0].Body,BackSteps[0].Nz);
      FloatDealloc_3D(BackSteps[0].Temp,BackSteps[0].Nz);

      NBackSteps--;

      for (i=0;i<NBackSteps;i++) BackSteps[i]=BackSteps[i+1];

   }

};

//vyma�e zp�tn� kroky z pam�ti  (dealokuje nclear nejstar��ch v��ez� z pam�ti)
void ClearUndo(BYTE nclear)
{
  int n,backsteps=NBackSteps;
  for (n=backsteps-1;n>backsteps-1-nclear;n--)
    {
      //dealokace pol� v�sek�
      ByteDealloc_3D(BackSteps[n].Body,BackSteps[n].Nz);
      FloatDealloc_3D(BackSteps[n].Temp,BackSteps[n].Nz);
      NBackSteps--;
    }
};


#endif