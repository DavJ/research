//---------------------------------------------------------------------------
#ifndef mcopyH
#define mcopyH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class Tfm_MCopy : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edFrom;
	TLabel *Label2;
	TEdit *edTo;
	TLabel *Label3;
	TEdit *edDest;
	TBitBtn *btn_OK;
	TBitBtn *btn_Cancel;
	TLabel *Label5;
	TLabel *Label6;
	void __fastcall btn_OKClick(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        WORD from,to,dest;
      	BYTE __fastcall MCopy();
	__fastcall Tfm_MCopy(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tfm_MCopy *fm_MCopy;
//---------------------------------------------------------------------------
#endif
