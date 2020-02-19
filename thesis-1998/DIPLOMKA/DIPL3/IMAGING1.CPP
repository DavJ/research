//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include "const.cpp"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("imaging.cpp", MainForm);
USEFORM("prog.cpp", Progress);
USEFORM("set1.cpp", ImMethod);
USEFORM("set2.cpp", Phantom);
USEFORM("set3.cpp", Form1);
USEUNIT("conf.cpp");
USEFORM("set4.cpp", SetColors);
USEFORM("About.cpp", fm_About);
USEFORM("set5.cpp", Hist);
USEFORM("phase.cpp", RefPhase);
USERES("imaging1.res");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "IMAGING";
		Application->HelpFile = "C:\\DIPLOMKA\\helpy\\Imaging.hlp";
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TImMethod), &ImMethod);
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TPhantom), &Phantom);
		Application->CreateForm(__classid(TProgress), &Progress);
		Application->CreateForm(__classid(TSetColors), &SetColors);
		Application->CreateForm(__classid(Tfm_About), &fm_About);
		Application->CreateForm(__classid(THist), &Hist);
		Application->CreateForm(__classid(TRefPhase), &RefPhase);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------

