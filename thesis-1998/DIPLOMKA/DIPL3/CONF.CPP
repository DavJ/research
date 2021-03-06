//---------------------------------------------------------------------------
#include <vcl\registry.hpp>
#pragma hdrstop

#include  "const.cpp"
TRegistry *Reg;
//---------------------------------------------------------------------------
//z�pis aktu�ln� konfigurace do syst�mov�ho registru
void WriteConfiguration()
{
     //z�pis konfigurace pou�it� zobrazovac� metody
     Reg->WriteInteger("Method",Method);
     Reg->WriteInteger("BegCond",BegCond);
     //z�pis konfigurace testovac�ho t�lesa
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
     //z�pis konfigurace souboru mg. pole
     Reg->WriteString("FieldName",FieldName);
     //z�pis konfigurace N_COLORS
     Reg->WriteInteger("N_COLORS",N_COLORS);
     Reg->WriteInteger("HistType",HistType);//typ p�evodn� charakteristiky
     Reg->WriteFloat("HistLog",HistLog); //z�klad logaritmick� p�evodn� charakteristiky

}
//---------------------------------------------------------------------------
//�ten� aktu�ln� konfigurace ze syst�mov�ho registru
void ReadConfiguration()
{

 //z�pis konfigurace pou�it� zobrazovac� metody
     Method=Reg->ReadInteger("Method");
     BegCond=Reg->ReadInteger("BegCond");

 //�ten� konfigurace testovac�ho t�lesa
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
 //�ten�  konfigurace souboru mg. pole
     sprintf(FieldName,"%s",Reg->ReadString("FieldName").c_str());
 //�ten�  konfigurace N_COLORS
     N_COLORS=Reg->ReadInteger("N_COLORS");

     HistType=Reg->ReadInteger("HistType");//typ p�evodn� charakteristiky
     HistLog=Reg->ReadFloat("HistLog"); //z�klad logaritmick� p�evodn� charakteristiky
}


//---------------------------------------------------------------------------
void LoadConfiguration()
{
 Reg=new TRegistry();

           Reg->OpenKey("SOFTWARE",true);
           Reg->OpenKey(GroupRootKey,true);
           if (!Reg->KeyExists(ImagingRootKey)) {
              Reg->OpenKey(ImagingRootKey,true);
              WriteConfiguration();   //z�pis default konfigurace do syst�mov�ho registru
                                 }
           else {
                Reg->OpenKey(ImagingRootKey,false);
                ReadConfiguration();   //�ten� aktu�ln� konfigurace ze syst�mov�ho registru
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
           WriteConfiguration();   //z�pis aktu�ln� konfigurace do syst�mov�ho registru
 delete Reg;
 }
