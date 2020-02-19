//---------------------------------------------------------------------------
#ifndef set1_BEH
#define set1_BEH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TEdit *edB0;
	TEdit *edTemp;
	TLabel *lbTemp;
	TLabel *lbB0;
	TLabel *lbFreq;
	
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *Label1;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall edB0Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
 