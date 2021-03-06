//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "set3.h"
#include "const.cpp"
#include "cfxocx2.h"
#include <float.h>
//---------------------------------------------------------------------------
#pragma link "ChartFX"
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
//definice n�stroj� pro toolbar tabulky a grafu
#define  TabTool CST_COPYDATA|CST_PRINT|CST_SPACE1|CST_SPACE2|CST_SPACE3|CST_SPACE4
#define  ChtTool CST_COPYBITMAP|CST_PRINT|CST_LEGGRID|CST_OPTIONS|CST_SPACE1|CST_SPACE2|CST_SPACE3|CST_SPACE4

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
  PField=&Field;
  PNewField=&NewField;
  LoadFieldName();      //nahraje nastaven� soubor magnetick�ho pole

}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetChartData(struct pulse_1D *PField)
{
 BYTE i,j;
 WORD points;
 float time1,time2;
 float ymax=FLT_MIN,ymin=FLT_MAX ;
 //char  ret[100];

 #define set_min     if (ymin>this->ChartFX1->Value[2*i]) ymin=this->ChartFX1->Value[2*i]
 #define set_max     if (ymax<this->ChartFX1->Value[2*i]) ymax=this->ChartFX1->Value[2*i]
 #define set_mima    set_min;set_max

 //nastaven� grafu podle prom�nn� PField

 points=2*PField->NI;

 this->ChartFX1->OpenDataEx(COD_VALUES,4,points);
 this->ChartFX1->OpenDataEx(COD_XVALUES,4,points);

 for (i=0;i<PField->NI;i++)
   {
    //a)y-hodnoty bod�  grafu
    //Gx
    this->ChartFX1->ThisSerie = 0;
	this->ChartFX1->Value[2*i]   = PField->Gx[i]/FieldUnit;
   	this->ChartFX1->Value[2*i+1] = this->ChartFX1->Value[2*i];

    set_mima;

    //Gy
    this->ChartFX1->ThisSerie = 1;
	this->ChartFX1->Value[2*i]   = PField->Gy[i]/FieldUnit;
   	this->ChartFX1->Value[2*i+1] = this->ChartFX1->Value[2*i];

    set_mima;

    //Gz
    this->ChartFX1->ThisSerie = 2;
	this->ChartFX1->Value[2*i]   = PField->Gz[i]/FieldUnit;
   	this->ChartFX1->Value[2*i+1] = this->ChartFX1->Value[2*i];

    set_mima;

    //B1
    this->ChartFX1->ThisSerie = 3;
	this->ChartFX1->Value[2*i]   = PField->B1[i]/FieldUnit;
   	this->ChartFX1->Value[2*i+1] = this->ChartFX1->Value[2*i];

    set_mima;

   //b)x-hodnoty bod�  grafu
    if (i==0) {time1=0;time2=PField->t[i]/TimeUnit;}
      else {time1=time2;time2+=PField->t[i]/TimeUnit;}

    for (j=0;j<4;j++)
      {
       this->ChartFX1->ThisSerie = j;
       this->ChartFX1->XValue[2*i]=time1;
	   this->ChartFX1->XValue[2*i+1]=time2;
      }

   }

    this->ChartFX1->CloseData(COD_XVALUES);
    this->ChartFX1->CloseData(COD_VALUES);


    this->ChartFX1->CustTool=ChtTool;
    this->ChartFX1->Type_|=Legend&CT_LEGEND; //vr�t� legendu do grafu (byla-li)



   this->ChartFX1->Adm[CSA_XMIN]=0;
   this->ChartFX1->Adm[CSA_XMAX]=time2;
   this->ChartFX1->Adm[CSA_MIN]=ymin;
   this->ChartFX1->Adm[CSA_MAX]=ymax;


   this->ChartFX1->SerLeg[0]="Gx [�T]";
   this->ChartFX1->SerLeg[1]="Gy [�T]";
   this->ChartFX1->SerLeg[2]="Gz [�T]";
   this->ChartFX1->SerLeg[3]="B1 [�T]";

   this->ChartFX1->Title[CHART_RIGHTTIT]="";
   this->ChartFX1->Title[CHART_TOPTIT]="";
   this->ChartFX1->Title[CHART_BOTTOMTIT]="t [ms]";
   this->ChartFX1->Title[CHART_LEFTTIT]=  "Gx, Gy, Gz, B1    [�T]";
   this->lbNI->Visible=false;this->edNI->Visible=false;
   this->lbB0->Visible=false;this->edB0->Visible=false;
   this->lbTs->Visible=false;this->edTs->Visible=false;

   #undef set_mima
   #undef  set_min
   #undef  set_max

}

//---------------------------------------------------------------------------
void __fastcall TForm1::SetEditorData(struct pulse_1D *PField)
{
 BYTE i,info;
 WORD points;
 char ret[100];

 //nastaven� grafu podle prom�nn� PField

 points=PField->NI;

 this->ChartFX1->OpenDataEx(COD_VALUES,7,points);

 for (i=0;i<PField->NI;i++)
  {
    //a)y-hodnoty bod�  grafu

    //t
    this->ChartFX1->ThisSerie = 0;
	this->ChartFX1->Value[i]   = PField->t[i]/TimeUnit;

    //Gx
    this->ChartFX1->ThisSerie = 1;
	this->ChartFX1->Value[i]   = PField->Gx[i]/FieldUnit;

    //Gy
    this->ChartFX1->ThisSerie = 2;
	this->ChartFX1->Value[i]   = PField->Gy[i]/FieldUnit;

    //Gz
    this->ChartFX1->ThisSerie = 3;
	this->ChartFX1->Value[i] = PField->Gz[i]/FieldUnit;

    //B1
    this->ChartFX1->ThisSerie = 4;
	this->ChartFX1->Value[i]   = PField->B1[i]/FieldUnit;

    //F1
    this->ChartFX1->ThisSerie = 5;
	this->ChartFX1->Value[i]   = PField->F1[i]/FreqUnit;

    //info ... informace o sn�mac�m a k�dovac�ch impulsech
    //         a zobrazen� hodnoty  p��r�stk�  gradientu na m�st� Gz,resp. Gy
    info=0;
    if (i==PField->Ngy-1) { //gy0
                          info|=1;
                          this->ChartFX1->ThisSerie = 2;
	                  this->ChartFX1->Value[i] = PField->gy0/FieldUnit;
                         }

    if (i==PField->Ngz-1) { //gz0
                          info|=2;
                          this->ChartFX1->ThisSerie = 3;
	                  this->ChartFX1->Value[i] = PField->gz0/FieldUnit;
                         }

    if (i==PField->NS-1)  info|=4; //sn�mac� impuls

    this->ChartFX1->ThisSerie = 6;//info
    this->ChartFX1->Value[i]  = info;
  }

  this->ChartFX1->CloseData(COD_VALUES);

  this->ChartFX1->CustTool=TabTool;
  Legend=this->ChartFX1->Type_&CT_LEGEND;
  this->ChartFX1->Type_&=~CT_LEGEND;       //odstran�n� legendy z tabulky


this->ChartFX1->SerLeg[0]="t  [ms]";
this->ChartFX1->SerLeg[1]="Gx [�T]";
this->ChartFX1->SerLeg[2]="Gy [�T]";
this->ChartFX1->SerLeg[3]="Gz [�T]";
this->ChartFX1->SerLeg[4]="B1 [�T]";
this->ChartFX1->SerLeg[5]="F1 [MHz]";
this->ChartFX1->SerLeg[6]="info";

//sprintf(ret,"%s%f","B0=",PField->B0);
//z�pis indukce pole
sprintf(ret,"%f",PField->B0);this->ChartFX1->Title[CHART_RIGHTTIT]=ret;
//z�pis vzorkovac� periody
sprintf(ret,"%f",NewTs);this->ChartFX1->Title[CHART_BOTTOMTIT]=ret;

this->lbNI->Visible=true;this->edNI->Visible=true;
this->lbB0->Visible=true;this->edB0->Visible=true;
this->lbTs->Visible=true;this->edTs->Visible=true;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::GetFieldData(struct pulse_1D *PField)
{
 BYTE i,info;
 WORD points;
 //char ret[100];
 float f;
 //nastaven� grafu podle prom�nn� PField

 points=this->ChartFX1->NValues;
 PField->NI=points;

 this->ChartFX1->OpenDataEx(COD_VALUES,COD_UNCHANGE,COD_UNCHANGE);

 for (i=0;i<points;i++)
  {
    //a)y-hodnoty bod�  grafu

    //t
    this->ChartFX1->ThisSerie = 0;
	PField->t[i]=this->ChartFX1->Value[i]*TimeUnit;

    //Gx
    this->ChartFX1->ThisSerie = 1;
	PField->Gx[i]=this->ChartFX1->Value[i]*FieldUnit;


    //Gy
    this->ChartFX1->ThisSerie = 2;
	PField->Gy[i]=this->ChartFX1->Value[i]*FieldUnit;

    //Gz
    this->ChartFX1->ThisSerie = 3;
	PField->Gz[i]=this->ChartFX1->Value[i]*FieldUnit;

    //B1
    this->ChartFX1->ThisSerie = 4;
	PField->B1[i]=this->ChartFX1->Value[i]*FieldUnit;

    //F1
    this->ChartFX1->ThisSerie = 5;
	PField->F1[i]=this->ChartFX1->Value[i]*FreqUnit;

    //info ... informace o sn�mac�m a k�dovac�ch impulsech
    this->ChartFX1->ThisSerie = 6;
    info=this->ChartFX1->Value[i];

    if (info&1) {//gy0
                 PField->Ngy=i+1;
                 this->ChartFX1->ThisSerie = 2;
                 PField->gy0=this->ChartFX1->Value[i]*FieldUnit;
                }

    if (info&2) {//gz0
                 PField->Ngz=i+1;
                 this->ChartFX1->ThisSerie = 3;
                 PField->gz0=this->ChartFX1->Value[i]*FieldUnit;
                }

    if (info&4)  PField->NS =i+1; //sn�mac� impulsy

  }

  this->ChartFX1->CloseData(COD_VALUES);
  //sprintf(ret,this->ChartFX1->Title[CHART_RIGHTTIT].c_str());
  //strcpy(ret,this->ChartFX1->Title[CHART_RIGHTTIT].c_str());
 //na�ten� indukce pole
 sscanf(this->ChartFX1->Title[CHART_RIGHTTIT].c_str(),"%f",&f);PField->B0=f;
 //na�ten� vzorkovac� periody
 sscanf(this->ChartFX1->Title[CHART_BOTTOMTIT].c_str(),"%f",&NewTs);
}


void __fastcall TForm1::Btn_OKClick(TObject *Sender)
{
 GetFieldData(PNewField);    //akceptov�n� zm�n proveden�ch v tabulce
 //akceptov�n� zm�n hodnot B0,Ts v editovac�ch ok�nk�ch
 sscanf(this->edTs->Text.c_str(),"%f",&(NewTs));
 sscanf(this->edB0->Text.c_str(),"%f",&(PNewField->B0));

 SetEditorData(PNewField);
 GetFieldData(PField);    //akceptov�n� zm�n mg.pole
 Ts=NewTs*TimeUnit;      //akceptov�n� zm�n vzorkovac� periody
 this->Hide();
 counted[n_sign]=false; //sign�l je nutno p�epo��tat
 counted[n_reko]=false; //rekonstrukci je nutno p�epo��tat

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_CancelClick(TObject *Sender)
{
/*  if (!CT_SHOWDATA&this->ChartFX1->Type_)  //bylo-li zru�eno z grafu
   {
    this->ChartFX1->Type_^=CT_SHOWDATA;
    SetChartData(PNewField);
    this->Btn_Switch->Caption="Tabulka";
   }      */

 this->btn_LoadField->Visible=true;   //zviditeln�n� tla��tka Otev��t
 this->btn_SaveField->Visible=true;   //zviditeln�n� tla��tka Ulo�it
 this->btn_Auto->Visible=true;       //zviditeln�n� tla��tka Gradienty
 this->Btn_OK->Visible=true;          //zviditeln�n� tla��tka OK

 this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_SwitchClick(TObject *Sender)
{

 this->Btn_Switch->Down^=1;
 this->ChartFX1->Type_^=CT_SHOWDATA;   //p�epnut� tabulka <-> graf
 this->btn_LoadField->Visible^=true;   //zneviditeln�n� tla��tka Otev��t
 this->btn_SaveField->Visible^=true;   //zneviditeln�n� tla��tka Ulo�it
 this->btn_Auto->Visible^=true;       //zneviditeln�n� tla��tka Gradienty
 this->Btn_OK->Visible^=true;          //zneviditeln�n� tla��tka OK


 if (CT_SHOWDATA&this->ChartFX1->Type_)
   {
    SetEditorData(PNewField);                 //inicializace tabulky
    this->Btn_Switch->Caption="Graf";
   }
  else {
        GetFieldData(PNewField);              //inicializace grafu daty z tabulky
        SetChartData(PNewField);
        this->Btn_Switch->Caption="Tabulka";
       }

 }

//---------------------------------------------------------------------------
void __fastcall TForm1::edNIKeyPress(TObject *Sender, char &Key)
{
char ret[100]="";
WORD d;
//potvrzen� ENTER
if (VkKeyScan(Key)==VK_RETURN) {
                GetFieldData(PNewField);
		sscanf(this->edNI->Text.c_str(),"%hu",&d);
                PNewField->NI=(d>MAX_IMP)? MAX_IMP:d;
                sprintf(ret," %u",PNewField->NI);this->edNI->Text=ret;
                SetEditorData(PNewField);
                                }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edNIEnter(TObject *Sender)
{
 Btn_OK->Default=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edNIExit(TObject *Sender)
{
/*  char ret[100]="";
  sprintf(ret," %u",PField->NI);this->edNI->Text=ret; */
  Btn_OK->Default=true;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::edB0Enter(TObject *Sender)
{
  Btn_OK->Default=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edB0Exit(TObject *Sender)
{
  Btn_OK->Default=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edB0KeyPress(TObject *Sender, char &Key)
{

//potvrzen� ENTER
if (VkKeyScan(Key)==VK_RETURN) {
                GetFieldData(PNewField);
                sscanf(this->edB0->Text.c_str(),"%f",&(PNewField->B0));
                SetEditorData(PNewField);
                               }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
 char ret[100]="";
 sprintf(ret," %u",PField->NI);this->edNI->Text=ret;
 sprintf(ret," %f",PField->B0);this->edB0->Text=ret;
 NewTs=Ts/TimeUnit;
 sprintf(ret," %f",NewTs);this->edTs->Text=ret;

 this->Btn_Switch->Caption="Graf";
 this->ChartFX1->Type_|=CT_SHOWDATA;

 SetEditorData(PField);
 this->lbFieldName->Caption=FieldName;
 }
//---------------------------------------------------------------------------
void __fastcall TForm1::ChartFX1ReadFile(TObject *Sender)
{
  char ret[100]="";
  GetFieldData(PNewField);
  sprintf(ret," %u",PNewField->NI);this->edNI->Text=ret;
  sprintf(ret," %f",PNewField->B0);this->edB0->Text=ret;
}
//---------------------------------------------------------------------------



#undef  TabTool
#undef  ChtTool

void __fastcall TForm1::btn_SaveFieldClick(TObject *Sender)
{
  SaveDialog1->Title="Ulo�en� souboru magnetick�ho pole";
  if (SaveDialog1->Execute())
  {
    sprintf(FieldName,"%s",SaveDialog1->FileName.c_str());
    this->lbFieldName->Caption=FieldName;
    GetFieldData(PNewField);
    //p�e�ten� aktu�ln�ch hodnot B0,Ts
    sscanf(this->edTs->Text.c_str(),"%f",&(NewTs));
    sscanf(this->edB0->Text.c_str(),"%f",&(PNewField->B0));
    SetEditorData(PNewField); //nastaven� t�chto hodnot v tabulce
    this->ChartFX1->ExportFile(SaveDialog1->FileName); //ulo�en�
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::btn_LoadFieldClick(TObject *Sender)
{
 char ret[100];
  OpenDialog1->Title="Otev�en� souboru magnetick�ho pole";
  if (OpenDialog1->Execute())
  {
    sprintf(FieldName,"%s",OpenDialog1->FileName.c_str());
    this->lbFieldName->Caption=FieldName;
    this->ChartFX1->ImportFile(OpenDialog1->FileName);

    GetFieldData(PNewField);
    //v�pis aktu�ln�ch hodnot NI,B0,Ts
    sprintf(ret," %u",PNewField->NI);this->edNI->Text=ret;
    sprintf(ret," %f",PNewField->B0);this->edB0->Text=ret;
    sprintf(ret," %f",NewTs);this->edTs->Text=ret;

    //sprintf(this->edTs->Text.c_str(),"%f",&(NewTs));
    //sscanf(this->edB0->Text.c_str(),"%f",&(PNewField->B0));
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFieldName()
{
 char ret [255];
 sprintf(ret,"%s%s%s","Nebyl nalezen soubor magnetick�ho pole ",FieldName," . Pracuje se s implicitn�mi hodnotami.");
 if (!this->ChartFX1->ImportFile(FieldName)) {
                                              //SetField1();
     					      MessageBox(NULL,ret,"Zpr�va",MB_OK);
     					     }

 else {  /*soubor byl nalezen*/
        GetFieldData(PNewField);    //akceptov�n� zm�n proveden�ch v tabulce

        //v�pis aktu�ln�ch hodnot NI,B0,Ts
        sprintf(ret," %u",PNewField->NI);this->edNI->Text=ret;
        sprintf(ret," %f",PNewField->B0);this->edB0->Text=ret;
        sprintf(ret," %f",NewTs);this->edTs->Text=ret;


        SetEditorData(PNewField);
        GetFieldData(PField);    //akceptov�n� zm�n mg.pole
        Ts=NewTs*TimeUnit;      //akceptov�n� zm�n vzorkovac� periody

        counted[n_sign]=false; //sign�l je nutno p�epo��tat
        counted[n_reko]=false; //rekonstrukci je nutno p�epo��tat
      }
}
void __fastcall TForm1::edTsKeyPress(TObject *Sender, char &Key)
{
//potvrzen� ENTER
if (VkKeyScan(Key)==VK_RETURN) {
                GetFieldData(PNewField);
                sscanf(this->edTs->Text.c_str(),"%f",&(NewTs));
                SetEditorData(PNewField);
                               }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_AutoClick(TObject *Sender)
{
 float ty,tz;  //d�lky trv�n� f�zovac�ch impuls�

 GetFieldData(PNewField);  //na�ten� aktu�ln�ch hodnot mg.impuls�
 //p�e�ten� aktu�ln�ch hodnot B0,Ts
 sscanf(this->edTs->Text.c_str(),"%f",&(NewTs));
 sscanf(this->edB0->Text.c_str(),"%f",&(PNewField->B0));

 ty=PNewField->t[PNewField->Ngy-1];   //d�lky gradientn�ch impuls�
 tz=PNewField->t[PNewField->Ngz-1];
 PNewField->Gx[PNewField->NS-1]=2*3.14159265359/(GamaH*Nx*NewTs*TimeUnit);  //velikost indexov�ho gradientu ve sm�ru j (x)
 PNewField->gy0=2*3.14159265359/(GamaH*Ny*ty);     //velikost kroku indexov�ho gradientu ve sm�ru i (y)
 PNewField->gz0=2*3.14159265359/(GamaH*Nz*tz);     //velikost kroku indexov�ho gradientu ve sm�ru i (z)
 SetRFPulses();                //nastav� hodnoty RF puls� podle sloupce info
 SetEditorData(PNewField);     //zobrazen� aktu�ln�ch hodnot v editoru
}
//---------------------------------------------------------------------------
//automatick� nastaven� amplitud RF impuls�
void __fastcall TForm1::SetRFPulses()
{
 BYTE i,info;

 this->ChartFX1->OpenDataEx(COD_VALUES,COD_UNCHANGE,COD_UNCHANGE);

 for (i=0;i<PNewField->NI;i++)
  {
    //info ... informace o sn�mac�m a k�dovac�ch impulsech a RF impulsech
    this->ChartFX1->ThisSerie = 6;
    info=this->ChartFX1->Value[i];

    if (info&8) {//90-stup�ov� RF impuls
                 PNewField->B1[i]=Pi/2/(GamaH*PNewField->t[i]);
                 PNewField->F1[i]=GamaH*PNewField->B0/(2*Pi);//rezonan�n� buzen�
                }

    if (info&16) {//180-stup�ov� RF impuls
                 PNewField->B1[i]=Pi/(GamaH*PNewField->t[i]);
                 PNewField->F1[i]=GamaH*PNewField->B0/(2*Pi);//rezonan�n� buzen�
                 }

  }

}
