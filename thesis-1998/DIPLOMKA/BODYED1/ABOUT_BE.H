//---------------------------------------------------------------------------
#ifndef About_BEH
#define About_BEH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfm_About : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *ProdName;
	TLabel *Author;
	TLabel *Company;
	TLabel *Version;
	TButton *btn_OK;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	

	void __fastcall btn_OKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfm_About(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tfm_About *fm_About;
//---------------------------------------------------------------------------
#endif
