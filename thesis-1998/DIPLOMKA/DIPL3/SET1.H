//---------------------------------------------------------------------------
#ifndef set1H
#define set1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "const.cpp"
//---------------------------------------------------------------------------
class TImMethod : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *RadioGroup1;
	TLabel *lbNx;
	TLabel *lbNy;
	TLabel *lbNz;
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TRadioGroup *RadioGroup2;
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TImMethod(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TImMethod *ImMethod;
//---------------------------------------------------------------------------
#endif
