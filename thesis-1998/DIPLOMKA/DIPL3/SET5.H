//---------------------------------------------------------------------------
#ifndef set5H
#define set5H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THist : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TRadioGroup *RadioGroup1;
	TLabel *lbA;
	TEdit *edA;
	void __fastcall RadioGroup1Click(TObject *Sender);
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THist(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern THist *Hist;
//---------------------------------------------------------------------------
#endif
