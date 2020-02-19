//---------------------------------------------------------------------------
#include <vcl\registry.hpp>
#pragma hdrstop

#include  "Const_BE.cpp"
TRegistry *Reg;
//---------------------------------------------------------------------------
//zápis aktuální konfigurace do systémového registru
void WriteConfiguration()
{
     //zápis konfigurace rozmìrù
     Reg->WriteInteger("Nx",Nx);
     Reg->WriteInteger("Ny",Ny);
     Reg->WriteInteger("Nz",Nz);

     //zápis konfigurace fyzikálních parametrù
     Reg->WriteFloat("B0",B0);
     Reg->WriteFloat("Temp",Temp);

     //zápis konfigurace tkánì pozadí
     Reg->WriteString("BcgTissName",BcgTissName);
     //zápis konfigurace N_COLORS
     Reg->WriteInteger("N_COLORS",N_COLORS);

}
//---------------------------------------------------------------------------
//ètení aktuální konfigurace ze systémového registru
void ReadConfiguration()
{
     //zápis konfigurace rozmìrù
     Nx=Reg->ReadInteger("Nx");
     Ny=Reg->ReadInteger("Ny");
     Nz=Reg->ReadInteger("Nz");

     //zápis konfigurace fyzikálních parametrù
     B0=Reg->ReadFloat("B0");
     Temp=Reg->ReadFloat("Temp");

     //zápis konfigurace tkánì pozadí
     sprintf(BcgTissName,"%s",Reg->ReadString("BcgTissName").c_str());

     //ètení  konfigurace N_COLORS
     N_COLORS=Reg->ReadInteger("N_COLORS");

}


//---------------------------------------------------------------------------
void LoadConfiguration()
{
 Reg=new TRegistry();

           Reg->OpenKey("SOFTWARE",true);
           Reg->OpenKey(GroupRootKey,true);
           if (!Reg->KeyExists(BodyedRootKey)) {
              Reg->OpenKey(BodyedRootKey,true);
              WriteConfiguration();   //zápis default konfigurace do systémového registru
                                 }
           else {
                Reg->OpenKey(BodyedRootKey,false);
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
           Reg->OpenKey(BodyedRootKey,true);
           WriteConfiguration();   //zápis aktuální konfigurace do systémového registru
 delete Reg;
 }
