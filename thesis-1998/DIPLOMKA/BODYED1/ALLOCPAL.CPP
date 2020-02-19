#ifndef _allocpalette
#define _allocpalette
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
//Alokace logicke palety pro n barev
LOGPALETTE *AllocLgPl(BYTE n)
{
 LOGPALETTE* plgpl;

 //alokace pamìti pro paletu a inicializace
 plgpl=(LOGPALETTE*)LocalAlloc(LPTR,sizeof(LOGPALETTE)+n*sizeof(PALETTEENTRY));
 plgpl->palNumEntries = n;
 plgpl->palVersion = 0x300;

 return plgpl;
}

//Alokace logicke palety pro n barev
void DeallocLgPl(LOGPALETTE* plgpl)
{
 LocalFree((HLOCAL) plgpl);
}
 #endif
