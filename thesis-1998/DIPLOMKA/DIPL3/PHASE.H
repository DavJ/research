//---------------------------------------------------------------------------
#ifndef phaseH
#define phaseH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TRefPhase : public TForm
{
__published:	// IDE-managed Components
	TEdit *edPhase1;
	TLabel *Label2;
	TLabel *Label3;
	TBitBtn *BitBtn1;
	TEdit *edPhase2;
	TLabel *Label1;
	TBitBtn *btn_Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall btn_CancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        
	__fastcall TRefPhase(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TRefPhase *RefPhase;
//---------------------------------------------------------------------------
#endif
