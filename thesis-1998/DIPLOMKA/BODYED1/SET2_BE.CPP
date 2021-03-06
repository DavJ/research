//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set2_BE.h"
#include "Const_BE.cpp"
#include "Alloc_nd.hpp"
#include "ImProc_BE.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_OKClick(TObject *Sender)
{

 WORD Mx,My,Mz;

 WORD i,j,k;
 BYTE ***aBod_N;
 float ***aTem_N;

 Mx=Nx;My=Ny;Mz=Nz;

 sscanf(this->edNx->Text.c_str(),"%hu",&Mx);
 sscanf(this->edNy->Text.c_str(),"%hu",&My);
 sscanf(this->edNz->Text.c_str(),"%hu",&Mz);

 if (Mx!=0) Mx=1<<(BYTE)ceil(log(Mx)/log(2)); else Mx=1;     //bere v�dy vy��� mocninu 2
 if (My!=0) My=1<<(BYTE)ceil(log(My)/log(2)); else My=1;
 if (Mz!=0) Mz=1<<(BYTE)ceil(log(Mz)/log(2)); else Mz=1;


if ((Mx!=Nx)||(My!=Ny)||(Mz!=Nz)) //do�lo-li ke zm�n� po�tu voxel�
 if (((Mx>=Nx)&&(My>=Ny)&&(Mz>=Nz))||(IDOK&Application->MessageBox("Nov� t�leso m� v n�kter�m sm�ru m�n� voxel�","V�straha",MB_OKCANCEL)))
 {
     aBod_N=ByteAlloc_3D(Mz,My,Mx);
     aTem_N=FloatAlloc_3D(Mz,My,Mx);

     for(i=0;i<Mx;i++)
       for(j=0;j<My;j++)
         for(k=0;k<Mz;k++)
           if ((i<Nx)&&(j<Ny)&&(k<Nz)) {
            				aBod_N[k][j][i]=aBody[k][j][i];
					aTem_N[k][j][i]=aTemp[k][j][i];
				       }
                   else                {
                                         aBod_N[k][j][i]=BcgTissue;
                                         aTem_N[k][j][i]=Temp;
                                       }
    ByteDealloc_3D(aBody,Nz);   //uvoln�n� p�vodn�ho t�lesa  z pam�ti
    FloatDealloc_3D(aTemp,Nz);
    ByteDealloc_2D(aView);

    Nx=Mx;Ny=My;Nz=Mz;
    aBody=aBod_N;aTemp=aTem_N;  //nastaven� glob�ln�ch ukazatel� na nov� t�leso
    aView=ByteAlloc_2D(Ny,Nx);
    if (PosZ>Nz-1) PosZ=Nz-1;   //nastaven� nov� pozice v t�lese
    if (Slider->Position>Nz-1) Slider->Position=Nz-1;//nastaven� nov�ho maxima slidru
    Slider->Max=Nz-1;           //nastaven� nov�ho maxima slidru
    if (Nz==1) Slider->Visible=false; else Slider->Visible=true; //zak�e scroll-bar u 2D t�lesa
 }
 sscanf(this->edBcgTissue->Text.c_str(),"%s",BcgTissName);
 BcgTissue=GetIndex(BcgTissName);  //zm�na tk�n� pozad�
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::btn_CancelClick(TObject *Sender)
{
  this->Hide(); //ignoruj zm�ny nastaven�
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormShow(TObject *Sender)
{
  char ret[100]="";
  sprintf(ret," %d",Nx);this->edNx->Text=ret;
  sprintf(ret," %d",Ny);this->edNy->Text=ret;
  sprintf(ret," %d",Nz);this->edNz->Text=ret;
  this->edBcgTissue->Text=BcgTissName;
}
//---------------------------------------------------------------------------
