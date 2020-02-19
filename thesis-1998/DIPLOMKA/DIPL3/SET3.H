//---------------------------------------------------------------------------
#ifndef set3H
#define set3H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "ChartFX.hpp"
#include <vcl\OleCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "const.cpp"
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TChartFX *ChartFX1;
	TBitBtn *Btn_OK;
	TBitBtn *Btn_Cancel;
	TLabel *lbNI;
	TEdit *edNI;
	TEdit *edB0;
	TLabel *lbB0;
	TSpeedButton *Btn_Switch;
	TSpeedButton *btn_SaveField;
	TSpeedButton *btn_LoadField;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TLabel *lbTs;
	TEdit *edTs;
	TSpeedButton *btn_Auto;
	TLabel *Label1;
	TLabel *lbFieldName;
	void __fastcall Btn_OKClick(TObject *Sender);
	void __fastcall Btn_CancelClick(TObject *Sender);
	void __fastcall Btn_SwitchClick(TObject *Sender);

	void __fastcall edNIKeyPress(TObject *Sender, char &Key);
	void __fastcall edNIEnter(TObject *Sender);
	void __fastcall edNIExit(TObject *Sender);


	void __fastcall edB0Enter(TObject *Sender);
	void __fastcall edB0Exit(TObject *Sender);
	void __fastcall edB0KeyPress(TObject *Sender, char &Key);

	void __fastcall FormShow(TObject *Sender);
	void __fastcall ChartFX1ReadFile(TObject *Sender);

	
	void __fastcall btn_SaveFieldClick(TObject *Sender);
	
	void __fastcall btn_LoadFieldClick(TObject *Sender);
	
	
	void __fastcall edTsKeyPress(TObject *Sender, char &Key);
	void __fastcall btn_AutoClick(TObject *Sender);
	
	
	
private:	// User declarations
        void __fastcall SetChartData(struct pulse_1D *Field);
        void __fastcall SetEditorData(struct pulse_1D *Field);
        void __fastcall GetFieldData(struct pulse_1D *Field);

        unsigned long   Legend;

public:		// User declarations
        struct pulse_1D *PField;
        struct pulse_1D *PNewField;
        float  NewTs;    //nová vzorkovací perioda
   void __fastcall LoadFieldName();
   void __fastcall SetRFPulses();
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
