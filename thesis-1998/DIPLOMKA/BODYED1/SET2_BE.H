//---------------------------------------------------------------------------
#ifndef set2_BEH
#define set2_BEH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TLabel *lbNx;
	TLabel *lbNy;
	TLabel *lbNz;
	TLabel *lbBcgTissue;
	TEdit *edNx;
	TEdit *edNy;
	TEdit *edNz;
	TEdit *edBcgTissue;
	
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
