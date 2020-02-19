//---------------------------------------------------------------------------
#ifndef editor_BEH
#define editor_BEH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\DB.hpp>
#include <vcl\DBTables.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDataSource *DataSource1;
	TTable *Table1;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TMainMenu *MainMenu1;
	TImage *Image;
	TPanel *Panel2;
	TLabel *lbPositionl;
	TLabel *lbTissuel;
	TLabel *lbT1l;
	TLabel *lbT2l;
	TLabel *lbM0l;
	TDBGrid *DBGrid1;
	TStringField *Table1TKAN;
	TStringField *Table1RED;
	TStringField *Table1GREEN;
	TStringField *Table1BLUE;
	TStringField *Table1A;
	TStringField *Table1B;
	TStringField *Table1T2;
	TStringField *Table1NPROT;
	TStringField *Table1T1;
	TScrollBar *ScrollBar1;
	TMenuItem *Nastaven1;
	TMenuItem *Fyziklnparametry1;
	TMenuItem *Zobrazen1;
	TPanel *Panel3;
	TDBGrid *DBGrid2;
	TMenuItem *Soubor1;
	TMenuItem *Novtk1;
	TMenuItem *Otevt1;
	TMenuItem *Uloit1;
	TMenuItem *Konec1;
	TMenuItem *Zobrazit1;
	TMenuItem *Tissue1;
	TMenuItem *Temperature1;
	TLabel *lbTempl;
	TLabel *lbPosition;
	TMenuItem *Paletu1;
	TPanel *Panel4;
	TSpeedButton *tl_undo;
	TSpeedButton *btn_point;
	TSpeedButton *tl_sphere;
	TSpeedButton *tl_cube;
	TSpeedButton *tl_rectangular;
	TSpeedButton *tl_elliptical;
	TSpeedButton *tl_cylinder;
	TImage *Color;
	TSpeedButton *btn_Copy;
	TSpeedButton *btn_t;
	TLabel *lbTissue;
	TLabel *lbT1;
	TLabel *lbT2;
	TLabel *lbM0;
	TLabel *lbTemp;
	TSpeedButton *btn_Temp;
	TSpeedButton *btn_Tissue;
	TStringField *Table1KT1;
	TStringField *Table1KT2;
	TMenuItem *Npovda1;
	TMenuItem *Info1;
	TMenuItem *Barvy1;
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall Table1CalcFields(TDataSet *DataSet);
	
	void __fastcall FormDestroy(TObject *Sender);

	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ImageClick(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	
	void __fastcall Fyziklnparametry1Click(TObject *Sender);
	void __fastcall Zobrazen1Click(TObject *Sender);
	void __fastcall Uloit1Click(TObject *Sender);

	
	
	
	
	
	
	
	
	
	void __fastcall Tissue1Click(TObject *Sender);
	void __fastcall Temperature1Click(TObject *Sender);
	void __fastcall Paletu1Click(TObject *Sender);
	void __fastcall tl_undoClick(TObject *Sender);
	void __fastcall btn_pointClick(TObject *Sender);
	void __fastcall tl_sphereMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall tl_sphereClick(TObject *Sender);
	void __fastcall tl_ellipticalClick(TObject *Sender);
	void __fastcall tl_rectangularClick(TObject *Sender);
	void __fastcall tl_cubeClick(TObject *Sender);
	void __fastcall tl_cylinderClick(TObject *Sender);


	void __fastcall btn_CopyClick(TObject *Sender);


	
	
	void __fastcall btn_tClick(TObject *Sender);
	
	void __fastcall btn_TempClick(TObject *Sender);
	void __fastcall btn_TissueClick(TObject *Sender);

	void __fastcall Konec1Click(TObject *Sender);
	void __fastcall Novtk1Click(TObject *Sender);
	void __fastcall Otevt1Click(TObject *Sender);
	void __fastcall Info1Click(TObject *Sender);
	void __fastcall Npovda1Click(TObject *Sender);
	void __fastcall Barvy1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
   void __fastcall TForm1::RefreshLabels();
   void __fastcall TForm1::InitColor();
   void __fastcall TForm1::ShowStatus(char *ret);
   void __fastcall ReadLUT();
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
