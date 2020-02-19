//---------------------------------------------------------------------------
#ifndef set2H
#define set2H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include "const.cpp"
//---------------------------------------------------------------------------
class TPhantom : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *Btn_OK;
	TBitBtn *Btn_Cancel;
	TLabel *lbNx;
	TLabel *lbNy;
	TLabel *lbNz;
	TEdit *edNx;
	TEdit *edNy;
	TEdit *edNz;
	TLabel *lbT1a;
	TEdit *edT1a;
	TLabel *lbT2a;
	TEdit *edT2a;
	TEdit *edT1b;
	TEdit *edT2b;
	TEdit *edM0a;
	TLabel *lbM0a;
	TEdit *edM0b;
	TLabel *lbT1b;
	TLabel *lbT2b;
	TLabel *lbM0b;
	TLabel *lbProp1;
	TLabel *lbProp2;
	TLabel *Label1;
	void __fastcall Btn_OKClick(TObject *Sender);
	void __fastcall Btn_CancelClick(TObject *Sender);
	
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void __fastcall TestingTissue(TISSUE *Tissue);
	__fastcall TPhantom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPhantom *Phantom;
//---------------------------------------------------------------------------
#endif
