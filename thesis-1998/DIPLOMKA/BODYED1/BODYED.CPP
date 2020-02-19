//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("editor_BE.cpp", Form1);
USERES("BODYED.res");
USEUNIT("allocpal.cpp");
USEUNIT("ImProc_BE.cpp");
USEUNIT("Const_BE.cpp");
USEFORM("set1_BE.cpp", Form4);
USEFORM("set2_BE.cpp", Form5);
USEUNIT("io_data.cpp");
USEFORM("tool.cpp", fm_Tool);
USEFORM("mcopy.cpp", fm_MCopy);
USEUNIT("undo.cpp");
USEFORM("temp.cpp", fm_Temp);
USEFORM("status.cpp", fm_Status);
USEFORM("About_BE.cpp", fm_About);
USEFORM("set4_BE.cpp", SetColors);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->HelpFile = "C:\\DIPLOMKA\\helpy\\Bodyed.hlp";
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->CreateForm(__classid(TForm5), &Form5);
		Application->CreateForm(__classid(Tfm_Tool), &fm_Tool);
		Application->CreateForm(__classid(Tfm_MCopy), &fm_MCopy);
		Application->CreateForm(__classid(Tfm_Temp), &fm_Temp);
		Application->CreateForm(__classid(Tfm_Status), &fm_Status);
		Application->CreateForm(__classid(Tfm_About), &fm_About);
		Application->CreateForm(__classid(TSetColors), &SetColors);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
