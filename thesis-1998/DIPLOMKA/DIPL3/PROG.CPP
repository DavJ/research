//#ifndef  _progression
//#define  _progression
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "prog.h"
#include "time.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TProgress *Progress;
//---------------------------------------------------------------------------
__fastcall TProgress::TProgress(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
char *TimeToStr(clock_t ticks,char *ret)
{
 BYTE hr,mn,sc;
 unsigned long sec=ticks/CLK_TCK;
 sc=sec%60;mn=(sec%3600)/60;hr=sec/3600;
 sprintf(ret,"%02d%c%02d%c%02d",hr,':',mn,':',sc);
 return(ret);
}
//---------------------------------------------------------------------------
void   __fastcall TProgress::Increment()
{
 char ret[100];
 this->ProgressBar1->StepIt();
 this->elapsed=clock()-this->start;
 this->remaining=(this->ProgressBar1->Max-this->ProgressBar1->Position)*(this->elapsed)/(float)this->ProgressBar1->Position;

 this->lbElapsed->Caption=TimeToStr(this->elapsed,ret);//this->lbElapsed->Repaint();
 this->lbRemaining->Caption=TimeToStr(this->remaining,ret);//this->lbRemaining->Repaint();
 //this->Repaint();
 Application->ProcessMessages();
 //this->ThisApplication->ProcessMessage();
}
//---------------------------------------------------------------------------
void   __fastcall TProgress::InitProgress(WORD max)
{
 this->Broken=false;
 this->ProgressBar1->Max=max;
 this->ProgressBar1->Min=0;
 this->ProgressBar1->Position=0;
 this->Show();
 this->start=clock();
 this->Repaint();
}
void __fastcall TProgress::Btn_CancelClick(TObject *Sender)
{
 //this->Hide();
 this->Broken=true;
}
//---------------------------------------------------------------------------
//#endif
