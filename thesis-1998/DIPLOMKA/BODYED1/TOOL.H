//---------------------------------------------------------------------------
#ifndef toolH
#define toolH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class Tfm_Tool : public TForm
{
__published:	// IDE-managed Components
	TLabel *lbA;
	TLabel *lbB;
	TLabel *lbC;
	TEdit *edA;
	TEdit *edB;
	TEdit *edC;
	TLabel *lbAlpha;
	TEdit *edAlpha;
	TLabel *lbBeta;
	TEdit *edBeta;
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TLabel *lbGama;
	TEdit *edGama;
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	
	void __fastcall FormShow(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
        BYTE ActiveTool;
	__fastcall Tfm_Tool(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tfm_Tool *fm_Tool;
//---------------------------------------------------------------------------
#endif
