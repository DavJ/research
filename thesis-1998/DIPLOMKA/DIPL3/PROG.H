//---------------------------------------------------------------------------
#ifndef progH
#define progH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "time.h"
//---------------------------------------------------------------------------
class TProgress : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *Btn_Cancel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *lbElapsed;
	TLabel *lbRemaining;
	TProgressBar *ProgressBar1;
	void __fastcall Btn_CancelClick(TObject *Sender);
	
	
private:	// User declarations
public:		// User declarations

  BYTE   Broken;
  clock_t start,elapsed,remaining;
  void  __fastcall Increment();
  void  __fastcall InitProgress(WORD max);
        __fastcall TProgress(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern TProgress *Progress;
//---------------------------------------------------------------------------
#endif
