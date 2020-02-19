//---------------------------------------------------------------------------
#include <vcl\registry.hpp>
#pragma hdrstop

#include  "const.cpp"
TRegistry *Reg;
//---------------------------------------------------------------------------
//zápis aktuální konfigurace do systémového registru
void WriteConfiguration()
{
     //zápis konfigurace použité zobrazovací metody
     Reg->WriteInteger("Method",Method);
     Reg->WriteInteger("BegCond",BegCond);
     //zápis konfigurace testovacího tìlesa
     Reg->WriteFloat("TestM0a",TestM0a);
     Reg->WriteFloat("TestT1a",TestT1a);
     Reg->WriteFloat("TestT2a",TestT2a);

     Reg->WriteFloat("TestM0b",TestM0b);
     Reg->WriteFloat("TestT1b",TestT1b);
     Reg->WriteFloat("TestT2b",TestT2b);

     Reg->WriteInteger("TestNx",TestNx);
     Reg->WriteInteger("TestNy",TestNy);
     Reg->WriteInteger("TestNz",TestNz);
     Reg->WriteInteger("TestType",TestType);
     //zápis konfigurace souboru mg. pole
     Reg->WriteString("FieldName",FieldName);
     //zápis konfigurace N_COLORS
     Reg->WriteInteger("N_COLORS",N_COLORS);
     Reg->WriteInteger("HistType",HistType);//typ pøevodní charakteristiky
     Reg->WriteFloat("HistLog",HistLog); //základ logaritmické pøevodní charakteristiky

}
//---------------------------------------------------------------------------
//ètení aktuální konfigurace ze systémového registru
void ReadConfiguration()
{

 //zápis konfigurace použité zobrazovací metody
     Method=Reg->ReadInteger("Method");
     BegCond=Reg->ReadInteger("BegCond");

 //ètení konfigurace testovacího tìlesa
     TestM0a=Reg->ReadFloat("TestM0a");
     TestT1a=Reg->ReadFloat("TestT1a");
     TestT2a=Reg->ReadFloat("TestT2a");

     TestM0b=Reg->ReadFloat("TestM0b");
     TestT1b=Reg->ReadFloat("TestT1b");
     TestT2b=Reg->ReadFloat("TestT2b");

     TestNx=Reg->ReadInteger("TestNx");
     TestNy=Reg->ReadInteger("TestNy");
     TestNz=Reg->ReadInteger("TestNz");
     TestType=Reg->ReadInteger("TestType");
 //ètení  konfigurace souboru mg. pole
     sprintf(FieldName,"%s",Reg->ReadString("FieldName").c_str());
 //ètení  konfigurace N_COLORS
     N_COLORS=Reg->ReadInteger("N_COLORS");

     HistType=Reg->ReadInteger("HistType");//typ pøevodní charakteristiky
     HistLog=Reg->ReadFloat("HistLog"); //základ logaritmické pøevodní charakteristiky
}


//---------------------------------------------------------------------------
void LoadConfiguration()
{
 Reg=new TRegistry();

           Reg->OpenKey("SOFTWARE",true);
           Reg->OpenKey(GroupRootKey,true);
           if (!Reg->KeyExists(ImagingRootKey)) {
              Reg->OpenKey(ImagingRootKey,true);
              WriteConfiguration();   //zápis default konfigurace do systémového registru
                                 }
           else {
                Reg->OpenKey(ImagingRootKey,false);
                ReadConfiguration();   //ètení aktuální konfigurace ze systémového registru
                }
 delete Reg;
 }
//---------------------------------------------------------------------------
void SaveConfiguration()
{
 Reg=new TRegistry();

           Reg->OpenKey("SOFTWARE",true);
           Reg->OpenKey(GroupRootKey,true);
           Reg->OpenKey(ImagingRootKey,true);
           WriteConfiguration();   //zápis aktuální konfigurace do systémového registru
 delete Reg;
 }
