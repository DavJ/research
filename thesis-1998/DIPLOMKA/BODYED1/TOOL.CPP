//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "tool.h"
#include "Const_BE.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
Tfm_Tool *fm_Tool;
//---------------------------------------------------------------------------
__fastcall Tfm_Tool::Tfm_Tool(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Tool::btn_OKClick(TObject *Sender)
{
  switch (ActiveTool) {
    case atlEll: sscanf(this->edA->Text.c_str(),"%f",&t_Ellipsoid_RadX);
 	 	 sscanf(this->edB->Text.c_str(),"%f",&t_Ellipsoid_RadY);
		 sscanf(this->edC->Text.c_str(),"%f",&t_Ellipsoid_RadZ);
		 sscanf(this->edAlpha->Text.c_str(),"%f",&t_Ellipsoid_Alpha);
		 sscanf(this->edBeta->Text.c_str(),"%f",&t_Ellipsoid_Beta);
		 sscanf(this->edGama->Text.c_str(),"%f",&t_Ellipsoid_Gama);
                 break;
    case atlRec: sscanf(this->edA->Text.c_str(),"%f",&t_Rectangular_a);
 		 sscanf(this->edB->Text.c_str(),"%f",&t_Rectangular_b);
		 sscanf(this->edC->Text.c_str(),"%f",&t_Rectangular_c);
		 sscanf(this->edAlpha->Text.c_str(),"%f",&t_Rectangular_Alpha);
		 sscanf(this->edBeta->Text.c_str(),"%f",&t_Rectangular_Beta);
		 sscanf(this->edGama->Text.c_str(),"%f",&t_Rectangular_Gama);
                 break;

    case atlCub: sscanf(this->edA->Text.c_str(),"%f",&t_Cube_a);
		 sscanf(this->edAlpha->Text.c_str(),"%f",&t_Cube_Alpha);
		 sscanf(this->edBeta->Text.c_str(),"%f",&t_Cube_Beta);
		 sscanf(this->edGama->Text.c_str(),"%f",&t_Cube_Gama);
                 break;

    case atlCyl: sscanf(this->edA->Text.c_str(),"%f",&t_Cylinder_r);
 		 sscanf(this->edB->Text.c_str(),"%f",&t_Cylinder_l);
		 sscanf(this->edAlpha->Text.c_str(),"%f",&t_Cylinder_Alpha);
		 sscanf(this->edBeta->Text.c_str(),"%f",&t_Cylinder_Beta);
		 sscanf(this->edGama->Text.c_str(),"%f",&t_Cylinder_Gama);
                 break;


    case atlSph: sscanf(this->edA->Text.c_str(),"%f",&t_Sphere_Rad);
                 break;
                    }
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Tool::btn_CancelClick(TObject *Sender)
{
 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall Tfm_Tool::FormShow(TObject *Sender)
{
 char ret[20];

 switch (ActiveTool) {
   case atlEll: sprintf(ret,"%.2f",t_Ellipsoid_RadX);this->edA->Text=ret;
 		sprintf(ret,"%.2f",t_Ellipsoid_RadY);this->edB->Text=ret;
	        sprintf(ret,"%.2f",t_Ellipsoid_RadZ);this->edC->Text=ret;
		sprintf(ret,"%.2f",t_Ellipsoid_Alpha);this->edAlpha->Text=ret;
		sprintf(ret,"%.2f",t_Ellipsoid_Beta);this->edBeta->Text=ret;
		sprintf(ret,"%.2f",t_Ellipsoid_Gama);this->edGama->Text=ret;
                this->Caption="Elipsoid";
                lbA->Caption="a";lbB->Caption="b";lbC->Caption="c";
                edB->Visible=true;edC->Visible=true;
                edAlpha->Visible=true;edBeta->Visible=true;edGama->Visible=true;
		lbB->Visible=true;lbC->Visible=true;
                lbAlpha->Visible=true;lbBeta->Visible=true;lbGama->Visible=true;

                break;
   case atlRec: sprintf(ret,"%.2f",t_Rectangular_a);this->edA->Text=ret;
 		sprintf(ret,"%.2f",t_Rectangular_b);this->edB->Text=ret;
		sprintf(ret,"%.2f",t_Rectangular_c);this->edC->Text=ret;
 		sprintf(ret,"%.2f",t_Rectangular_Alpha);this->edAlpha->Text=ret;
 		sprintf(ret,"%.2f",t_Rectangular_Beta);this->edBeta->Text=ret;
 		sprintf(ret,"%.2f",t_Rectangular_Gama);this->edGama->Text=ret;
                this->Caption="Kvádr";
                edB->Visible=true;edC->Visible=true;
                edAlpha->Visible=true;edBeta->Visible=true;edGama->Visible=true;
                lbB->Visible=true;lbC->Visible=true;
                lbAlpha->Visible=true;lbBeta->Visible=true;lbGama->Visible=true;
                lbA->Caption="a";lbB->Caption="b";lbC->Caption="c";

                break;
   case atlCub: sprintf(ret,"%.2f",t_Cube_a);this->edA->Text=ret;
 		sprintf(ret,"%.2f",t_Cube_Alpha);this->edAlpha->Text=ret;
 		sprintf(ret,"%.2f",t_Cube_Beta);this->edBeta->Text=ret;
 		sprintf(ret,"%.2f",t_Cube_Gama);this->edGama->Text=ret;
                this->Caption="Krychle";
                edB->Visible=false;edC->Visible=false;
                edAlpha->Visible=true;edBeta->Visible=true;edGama->Visible=true;
                lbB->Visible=false;lbC->Visible=false;
                lbAlpha->Visible=true;lbBeta->Visible=true;lbGama->Visible=true;
                lbA->Caption="a";
                break;

  case atlCyl:  sprintf(ret,"%.2f",t_Cylinder_r);this->edA->Text=ret;
 		sprintf(ret,"%.2f",t_Cylinder_l);this->edB->Text=ret;
 		sprintf(ret,"%.2f",t_Cylinder_Alpha);this->edAlpha->Text=ret;
 		sprintf(ret,"%.2f",t_Cylinder_Beta);this->edBeta->Text=ret;
 		sprintf(ret,"%.2f",t_Cylinder_Gama);this->edGama->Text=ret;
                this->Caption="Válec";
                edB->Visible=true;edC->Visible=false;
                edAlpha->Visible=true;edBeta->Visible=true;edGama->Visible=true;
                lbB->Visible=true;lbC->Visible=false;
                lbAlpha->Visible=true;lbBeta->Visible=true;lbGama->Visible=true;
                lbA->Caption="polomìr";lbB->Caption="délka";

                break;


   case atlSph: sprintf(ret,"%.2f",t_Sphere_Rad);this->edA->Text=ret;
                this->Caption="Koule";
                edB->Visible=false;edC->Visible=false;
                edAlpha->Visible=false;edBeta->Visible=false;edGama->Visible=false;
                lbB->Visible=false;lbC->Visible=false;
                lbAlpha->Visible=false;lbBeta->Visible=false;lbGama->Visible=false;
                lbA->Caption="polomìr";
                break;
                   }
}
//---------------------------------------------------------------------------
