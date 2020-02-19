//---------------------------------------------------------------------------
#ifndef tempH
#define tempH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class Tfm_Temp : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TEdit *edTemp;
	TLabel *lbTemp;
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm_Temp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tfm_Temp *fm_Temp;
//---------------------------------------------------------------------------
#endif
