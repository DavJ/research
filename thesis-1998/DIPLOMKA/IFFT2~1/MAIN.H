//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Messages.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *FileNewItem;
	TMenuItem *FileOpenItem;
	TMenuItem *FileCloseItem;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *N1;
	TMenuItem *FileExitItem;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TOpenDialog *OpenDialog;
	TMenuItem *FileSaveItem;
	TMenuItem *FileSaveAsItem;
	TMenuItem *Edit1;
	TMenuItem *CutItem;
	TMenuItem *CopyItem;
	TMenuItem *PasteItem;
	TMenuItem *WindowMinimizeItem;
	TPanel *SpeedPanel;
	TSpeedButton *OpenBtn;
	TSpeedButton *SaveBtn;
	TSpeedButton *CutBtn;
	TSpeedButton *CopyBtn;
	TSpeedButton *PasteBtn;
	TSpeedButton *ExitBtn;
	TStatusBar *StatusBar;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FileNewItemClick(TObject *Sender);
	void __fastcall WindowCascadeItemClick(TObject *Sender);
	void __fastcall UpdateMenuItems(TObject *Sender);
	void __fastcall WindowTileItemClick(TObject *Sender);
	void __fastcall WindowArrangeItemClick(TObject *Sender);
	void __fastcall FileCloseItemClick(TObject *Sender);
	void __fastcall FileOpenItemClick(TObject *Sender);
	void __fastcall FileExitItemClick(TObject *Sender);
	void __fastcall FileSaveItemClick(TObject *Sender);
	void __fastcall FileSaveAsItemClick(TObject *Sender);
	void __fastcall CutItemClick(TObject *Sender);
	void __fastcall CopyItemClick(TObject *Sender);
	void __fastcall PasteItemClick(TObject *Sender);
	void __fastcall WindowMinimizeItemClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
    
private:
	void __fastcall CreateMDIChild(const String Name);
	void __fastcall ShowHint(TObject *Sender);
public:
	virtual __fastcall TMainForm(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif    
