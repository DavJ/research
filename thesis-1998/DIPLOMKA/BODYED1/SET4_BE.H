//---------------------------------------------------------------------------
#ifndef set4_BEH
#define set4_BEH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TSetColors : public TForm
{
__published:	// IDE-managed Components
	TEdit *edNColors;
	TLabel *lbNcol;
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	void __fastcall btn_CancelClick(TObject *Sender);
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSetColors(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSetColors *SetColors;
//---------------------------------------------------------------------------
#endif
