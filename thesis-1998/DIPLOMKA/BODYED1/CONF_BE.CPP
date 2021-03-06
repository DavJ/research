//---------------------------------------------------------------------------
#include <vcl\registry.hpp>
#pragma hdrstop

#include  "Const_BE.cpp"
TRegistry *Reg;
//---------------------------------------------------------------------------
//z�pis aktu�ln� konfigurace do syst�mov�ho registru
void WriteConfiguration()
{
     //z�pis konfigurace rozm�r�
     Reg->WriteInteger("Nx",Nx);
     Reg->WriteInteger("Ny",Ny);
     Reg->WriteInteger("Nz",Nz);

     //z�pis konfigurace fyzik�ln�ch parametr�
     Reg->WriteFloat("B0",B0);
     Reg->WriteFloat("Temp",Temp);

     //z�pis konfigurace tk�n� pozad�
     Reg->WriteString("BcgTissName",BcgTissName);
     //z�pis konfigurace N_COLORS
     Reg->WriteInteger("N_COLORS",N_COLORS);

}
//---------------------------------------------------------------------------
//�ten� aktu�ln� konfigurace ze syst�mov�ho registru
void ReadConfiguration()
{
     //z�pis konfigurace rozm�r�
     Nx=Reg->ReadInteger("Nx");
     Ny=Reg->ReadInteger("Ny");
     Nz=Reg->ReadInteger("Nz");

     //z�pis konfigurace fyzik�ln�ch parametr�
     B0=Reg->ReadFloat("B0");
     Temp=Reg->ReadFloat("Temp");

     //z�pis konfigurace tk�n� pozad�
     sprintf(BcgTissName,"%s",Reg->ReadString("BcgTissName").c_str());

     //�ten�  konfigurace N_COLORS
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
              WriteConfiguration();   //z�pis default konfigurace do syst�mov�ho registru
                                 }
           else {
                Reg->OpenKey(BodyedRootKey,false);
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
           Reg->OpenKey(BodyedRootKey,true);
           WriteConfiguration();   //z�pis aktu�ln� konfigurace do syst�mov�ho registru
 delete Reg;
 }
