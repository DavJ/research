//---------------------------------------------------------------------------
#ifndef statusH
#define statusH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class Tfm_Status : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall Tfm_Status(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tfm_Status *fm_Status;
//---------------------------------------------------------------------------
#endif
