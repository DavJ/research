//---------------------------------------------------------------------------
#ifndef imagingH
#define imagingH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
#include "ChartFX.hpp"
#include <vcl\OleCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ComCtrls.hpp>

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TMainMenu *MainMenu1;
	TMenuItem *Soubor1;
	TMenuItem *Zobraz1;
	TMenuItem *Otevt1;
	TMenuItem *Ulozit;
	TMenuItem *Paletu1;
	TMenuItem *Konec1;
	TMenuItem *Pomoc1;
	TMenuItem *Signl1;
	TMenuItem *Rekonstrukce1;
	TMenuItem *Tk1;
	TMenuItem *T11;
	TMenuItem *T21;
	TMenuItem *M01;
	TMenuItem *My1;
	TMenuItem *real1;
	TMenuItem *imag1;
	TOpenDialog *OpenDialog1;
	TPanel *Panel1;
	TScrollBar *ScrollBar1;
	TLabel *lbPos;
	TMenuItem *Nastaven1;
	TMenuItem *FFT1;
	TMenuItem *SetShowing;
	TMenuItem *SetTest;
	TMenuItem *Testovactleso1;
	TMenuItem *SetField;
	TSaveDialog *SaveDialog1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *lbValue;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *lbMin;
	TLabel *lbMax;
	TMenuItem *Ncolors1;
	TSpeedButton *btn_M0;
	TSpeedButton *btn_T1;
	TSpeedButton *btn_T2;
	TSpeedButton *btn_Mx;
	TSpeedButton *btn_My;
	TSpeedButton *btn_Im;
	TPanel *Panel2;
	TSpeedButton *btn_Re;
	TMenuItem *Info1;
	TMenuItem *Npovda1;
	TMenuItem *N2DFFT1;
	TMenuItem *N2DIFFT1;
	TMenuItem *N2Dkorekce1;
	TMenuItem *N3Dkorekce1;
	TMenuItem *N3Dreal1;
	TMenuItem *N3Dimag1;
	TMenuItem *IFFTsignlu1;
	TMenuItem *N2Dreal1;
	TMenuItem *N2Dimag1;
	TMenuItem *N3Dreal2;
	TMenuItem *N3Dimag2;
	TMenuItem *N3Dreal3;
	TMenuItem *N3Dimag3;
	TMenuItem *Histogram1;
	TLabel *Label5;
	TLabel *lbHist;
	TMenuItem *Mx1;
	TMenuItem *SetPhase;
	TSpeedButton *SpeedButton1;
	TMenuItem *Korigovansignl1;
	TMenuItem *N2;
	void __fastcall FormCreate(TObject *Sender);
	
	

	void __fastcall Paletu1Click(TObject *Sender);
	void __fastcall Konec1Click(TObject *Sender);
	



	

	void __fastcall M01Click(TObject *Sender);
	void __fastcall Mx1Click(TObject *Sender);
	void __fastcall real1Click(TObject *Sender);
	
	void __fastcall Otevt1Click(TObject *Sender);
	void __fastcall UlozitClick(TObject *Sender);
	

	void __fastcall imag1Click(TObject *Sender);
	
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X,
	int Y);
	void __fastcall T11Click(TObject *Sender);
	void __fastcall T21Click(TObject *Sender);

	
	void __fastcall Real2Click(TObject *Sender);
	void __fastcall Imag2Click(TObject *Sender);
	void __fastcall Real3Click(TObject *Sender);
	void __fastcall Imag3Click(TObject *Sender);
	void __fastcall Real4Click(TObject *Sender);
	void __fastcall Imag4Click(TObject *Sender);
	void __fastcall All1Click(TObject *Sender);

	void __fastcall SetShowingClick(TObject *Sender);

	

	void __fastcall SetTestClick(TObject *Sender);

	void __fastcall My1Click(TObject *Sender);
	void __fastcall Testovactleso1Click(TObject *Sender);
	
	void __fastcall SetFieldClick(TObject *Sender);


	void __fastcall Ncolors1Click(TObject *Sender);
	
	
	
	
	
	void __fastcall FormDestroy(TObject *Sender);
	
	void __fastcall Info1Click(TObject *Sender);
	void __fastcall Npovda1Click(TObject *Sender);
	
	
	
	
	void __fastcall N2Dkorekce1Click(TObject *Sender);
	void __fastcall N3Dkorekce1Click(TObject *Sender);
	void __fastcall N3Dreal1Click(TObject *Sender);
	void __fastcall N3Dimag1Click(TObject *Sender);
	
	void __fastcall N3Dreal3Click(TObject *Sender);
	void __fastcall N2DFFT1Click(TObject *Sender);
	void __fastcall N2DIFFT1Click(TObject *Sender);
	void __fastcall N3Dimag3Click(TObject *Sender);
	void __fastcall N2Dreal1Click(TObject *Sender);
	void __fastcall N2Dimag1Click(TObject *Sender);
	void __fastcall N3Dreal2Click(TObject *Sender);
	void __fastcall N3Dimag2Click(TObject *Sender);
	void __fastcall Histogram1Click(TObject *Sender);



	void __fastcall SetPhaseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   void __fastcall RefreshLabels();
   void __fastcall RefreshImage(TImage *Image,BYTE active);
   void __fastcall EnableAllButtons();
   void __fastcall DisableAllButtons();
   void __fastcall EnableTissButtons();
   void __fastcall DisableTissButtons();

   void __fastcall ShowMessage(BYTE msg);

	__fastcall TMainForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
