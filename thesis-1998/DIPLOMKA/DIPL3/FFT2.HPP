#ifndef  _fourier
#define  _fourier

#include    <complex.h>
#include    <alloc.h>
#include    "alloc_nd.hpp"  // knihovna alokujici n-rozmerne pole

#define Iu  complex(0,1) // imaginarni jednotka
#define Pi  acos(-1)     // 3.142 ...
#define order(N) floor(0.5+log(N)/log(2))


/*
Dvourozmerna rychla fourierova transformace
algoritmus decimace v  case (TID)

s ..  ukazatel na 2D pole  s N1xN2 vzorky realneho(double) obrazu,
      ktery  ma byt transformovan.
      Funkce predpoklada ulozeni po radcich tj. prvek
      pole s[i][j] vyjadruje hodnotu obrazoveho vzorku na i-tem radku
      v j-tem sloupci (i=0..N1-1 j=0..N2-1)

f ..  ukazatel na 2D pole typu complex velikosti N1xN2 kam maji byt  ulozeny
      hodnoty spektralnich slozek. Organizace prvku je obdobna jako u s
      tj. ve vyrazu f[i][j] odpovidaji indexy i,j prostorovym frekvencim
      v patricnem smeru (opet i=0..N1-1 j=0..N2-1)

m1,m2 ..  rad Fourierovy transformace ve smeru i resp. j
	  plati N1=2**m1 a N2=2**m2 , kde N1  je pocet radku
	  a N2 pocet sloupcu obrazu.

*/
int fft2(complex huge **s,complex huge **f,WORD  m1,WORD m2)
{
  WORD i,j,k,l;       // indexy smycek
  WORD i1,i2;         // indexy operandu v motylku
  WORD N1=1<<m1;      // pocet radek matice obrazu
  WORD N2=1<<m2;      // pocet sloupcu matice obrazu
  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  fft
  complex  Wi;                // i-ta mocnina vektoru W

  complex huge **fm;               //ukazatel na pole mezivysledku fft(po 1D fft podle radek)
  WORD *bitinv;	      // ukazatel na pole bitove inverznich indexu

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  if((bitinv=(WORD *)calloc((N1>N2)?N1:N2,sizeof(int)))==NULL) return(1); //chyba 1
  if((fm=CplxAlloc_2D(N1,N2))==NULL) {free(bitinv);
				      return(2);//chyba 2
				     };
//<A> FOURIEROVA TRANSFORMACE PODEL RADEK

  //vypocet bitove inverzniho pole
  for  (i=0;i<N2;i++)       // smycka i - projizdi vsechny sloupce
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m2;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m2-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }


  for (l=0;l<N1;l++)           //smycka l - smycka projizdi vsechny radky
    {
   //bitova inverze radku
     for  (i=0;i<N2;i++)           // smycka i - projizdi vsechny sloupce
       fm[l][i]=s[l][bitinv[i]];	   //bitove preusporadani l-teho radku

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  fft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  fft) v jedne dilci fft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci fft
  */
    for (k=1;k<N2;k<<=1)
      {
	W=exp(-Iu*Pi/k); // komplexni  vektor W ..jadro dilci fft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci fft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci fft
	*/

	for (j=0;j<N2;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;  //  inicializace dilci fft Wi=W**1;
	    i1=j;  //  index horniho operandu v  motylku
	    i2=j+k;//  index dolniho operandu  v motylku

	    nas=fm[l][i2];
	    fm[l][i2]=fm[l][i1]-nas;  // vlastni motylek pro i=0;
	    fm[l][i1]=fm[l][i1]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=fm[l][i2]*Wi;

	       fm[l][i2]=fm[l][i1]-nas;  // vlastni motylek
	       fm[l][i1]=fm[l][i1]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }
   }

//<B> FOURIEROVA TRANSFORMACE PODEL SLOUPCU

  //vypocet bitove inverzniho pole
  for  (i=0;i<N1;i++)       // smycka i - projizdi vsechny radky
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m1;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m1-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

  for (l=0;l<N2;l++)          //smycka l - smycka projizdi vsechny sloupce
    {
   //bitova inverze sloupce
     for  (i=0;i<N1;i++)           // smycka i - projizdi vsechny radky
       f[i][l]=fm[bitinv[i]][l];	   //bitove preusporadani l-teho sloupce

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  fft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  fft) v jedne dilci fft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci fft
  */
    for (k=1;k<N1;k<<=1)
      {
	W=exp(-Iu*Pi/k); // komplexni  vektor W ..jadro dilci fft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci fft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci fft
	*/

	for (j=0;j<N1;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;  //  inicializace dilci fft Wi=W**1;
	    i1=j;  //  index horniho operandu v  motylku
	    i2=j+k;//  index dolniho operandu  v motylku

	    nas=f[i2][l];
	    f[i2][l]=f[i1][l]-nas;  // vlastni motylek pro i=0;
	    f[i1][l]=f[i1][l]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=f[i2][l]*Wi;

	       f[i2][l]=f[i1][l]-nas;  // vlastni motylek
	       f[i1][l]=f[i1][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }

 //uvolneni pomocnych poli z pameti
 CplxDealloc_2D(fm);
 free(bitinv);
 return(0);		//fft probehla uspesne
};


//---------------------------------------------------------------------------

/*
Dvourozmerna rychla inverzní fourierova transformace
algoritmus decimace v  case (TID)

s ..  ukazatel na 2D pole  s N1xN2 vzorky komplexního spektra obrazu,
      ktery  ma byt transformovan.
      Ve vyrazu s[i][j] odpovidaji indexy i,j prostorovym frekvencim
      v patricnem smeru (opet i=0..N1-1 j=0..N2-1)
	     
f ..  ukazatel na 2D pole (typu complex !) velikosti N1xN2 kam maji byt
      ulozeny hodnoty vzorkù obrazu. Funkce provádí uložení po radcich tj. prvek
      pole f[i][j] vyjadruje hodnotu vzorku obrazu  spektra  na i-tem radku
      v j-tem sloupci (i=0..N1-1 j=0..N2-1)

      
m1,m2 ..  rad inverzní Fourierovy transformace ve smeru i resp. j
	  plati N1=2**m1 a N2=2**m2 , kde N1  je pocet radku
	  a N2 pocet sloupcu obrazu.

*/







int ifft2(complex huge **s,complex huge **f,WORD  m1,WORD m2)
{
  WORD i,j,k,l;       // indexy smycek
  WORD i1,i2;         // indexy operandu v motylku
  WORD N1=1<<m1;      // pocet radek matice obrazu
  WORD N2=1<<m2;      // pocet sloupcu matice obrazu
  unsigned long int D=N1*N2;  // dìlitel  D=Nx*Ny	ROZDíL PROTI FFT !!!
  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  ifft
  complex  Wi;                // i-ta mocnina vektoru W

  complex huge **fm;               //ukazatel na pole mezivysledku ifft(po 1D ifft podle radek)
  WORD *bitinv;	      // ukazatel na pole bitove inverznich indexu

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  if((bitinv=(WORD *)calloc((N1>N2)?N1:N2,sizeof(int)))==NULL) return(1); //chyba 1
  if((fm=CplxAlloc_2D(N1,N2))==NULL) {free(bitinv);
				      return(2);//chyba 2
				     };
//<A> INVERZNí FOURIEROVA TRANSFORMACE PODEL RADEK

  //vypocet bitove inverzniho pole
  for  (i=0;i<N2;i++)       // smycka i - projizdi vsechny sloupce
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m2;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m2-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

  
  for (l=0;l<N1;l++)           //smycka l - smycka projizdi vsechny radky
    {
   //bitova inverze radku
     for  (i=0;i<N2;i++)            // smycka i - projizdi vsechny sloupce
       fm[l][i]=s[l][bitinv[i]]/D;  //bitove preusporadani l-teho radku 
				    //a dìlení signálu Nx*Ny ROZDíL PROTI FFT !!!	

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  ifft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  ifft) v jedne dilci ifft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci ifft
  */
    for (k=1;k<N2;k<<=1)
      {
			 //ROZDíL PROTI fft !!! ve znaménku exponentu	
	W=exp(+Iu*Pi/k); // komplexni  vektor W ..jadro dilci ifft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci ifft
	*/

	for (j=0;j<N2;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
  	    Wi=W;  //  inicializace dilci fft Wi=W**1
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

	    nas=fm[l][i2];
	    fm[l][i2]=fm[l][i1]-nas;  // vlastni motylek pro i=0;
	    fm[l][i1]=fm[l][i1]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=fm[l][i2]*Wi;

	       fm[l][i2]=fm[l][i1]-nas;  // vlastni motylek
	       fm[l][i1]=fm[l][i1]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }
   }

//<B> FOURIEROVA TRANSFORMACE PODEL SLOUPCU

  //vypocet bitove inverzniho pole
  for  (i=0;i<N1;i++)       // smycka i - projizdi vsechny radky
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m1;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m1-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

  for (l=0;l<N2;l++)          //smycka l - smycka projizdi vsechny sloupce
    {
   //bitova inverze sloupce 
     for  (i=0;i<N1;i++)           // smycka i - projizdi vsechny radky
       f[i][l]=fm[bitinv[i]][l];	   //bitove preusporadani l-teho sloupce

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  ifft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  ifft) v jedne dilci ifft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci ifft
  */
    for (k=1;k<N1;k<<=1)
      {	          	 // ROZDíL PROTI fft !!! - ve znaménku exponentu	
	W=exp(+Iu*Pi/k); // komplexni  vektor W ..jadro dilci ifft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci ifft
	*/

	for (j=0;j<N1;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/		      
	    Wi=W;     //  inicializace dilci fft Wi=W**1;
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

	    nas=f[i2][l];
	    f[i2][l]=f[i1][l]-nas;  // vlastni motylek pro i=0;
	    f[i1][l]=f[i1][l]+nas;

       // smycka i .. vypocet dilci ifft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=f[i2][l]*Wi;

	       f[i2][l]=f[i1][l]-nas;  // vlastni motylek
	       f[i1][l]=f[i1][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }


 //uvolneni pomocnych poli z pameti
 CplxDealloc_2D(fm);
 free(bitinv);
 return(0);		//ifft probehla uspesne
};



//***********************************************************************
//--------------------- TROJROZMÌRNÌ ------------------------------------
//***********************************************************************


//************************** PØÍMÁ ***************************************
int fft3(complex huge ***s,complex huge ***f,WORD m3,WORD m2,WORD  m1)
{
  WORD i,j,k,l,m;       // indexy smycek
  WORD i1,i2;           // indexy operandu v motylku
  WORD N1=1<<m1;        // x -ový rozmìr tìlesa
  WORD N2=1<<m2;        // y -ový rozmìr tìlesa
  WORD N3=1<<m3;        // z- ový rozmìr tìlesa
  WORD Nmax;		    //maximální rozmìr tìlesa

  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  fft
  complex  Wi;                // i-ta mocnina vektoru W

  //complex huge *W;           //ukazatel na tabulku mocnin jádra ifft (index==mocnina)
  WORD *bitinv;	             //ukazatel na tabulku bitove inverznich indexù

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  Nmax=((Nmax=(N1>N2)? N1:N2)>N3)? Nmax:N3; //urèení maximálního rozmìru tìlesa
  if((bitinv=(WORD *)calloc(Nmax,sizeof(WORD)))==NULL) return(1); //chyba 1

/*  if ((W=(complex huge*)farcalloc(Nmax,sizeof(complex)))==NULL)
                     {
					   farfree(fb);
                       free(bitinv);
                       return(2);//chyba 2
				     };                     */





//<A>  FOURIEROVA TRANSFORMACE PODEL OSY X

  //vypocet bitove inverzniho pole
  for  (i=0;i<N1;i++)       // smycka i - vsechny x ove souradnice
    {
     /// W[i]=exp(+Iu*i*Pi/k); // komplexni  vektor W ..jadro dilci fft

      k=0;		                        //inicializace bitove inverzniho indexu
      for (j=0;j<m1;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m1-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N3;m++)             //smycka m - smycka projizdi vsechny z souøadnice
  for (l=0;l<N2;l++)           //smycka l - smycka projizdi vsechny y souøadnice
    {
   //1D-x pøeuspoøádání
     for  (i=0;i<N1;i++)                  // smycka i - projizdi vsechny x souøadnice
       f[m][l][i]=s[m][l][bitinv[i]];          //1D-x bitove preusporadani


  // algoritmus  TID-motylek -podel osy x
  // smycka  k .. etapa  fft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  fft) v jedne dilci fft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci fft
  */
    for (k=1;k<N1;k<<=1)
      {
 	   W=exp(-Iu*Pi/k); // komplexni  vektor W ..jadro dilci fft
		            	// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci fft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci fft
	*/

	for (j=0;j<N1;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
  	    Wi=W;  //  inicializace dilci fft Wi=W**1
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

        nas=f[m][l][i2];
	    f[m][l][i2]=f[m][l][i1]-nas;  // vlastni motylek pro i=0;
	    f[m][l][i1]=f[m][l][i1]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=f[m][l][i2]*Wi;

	       f[m][l][i2]=f[m][l][i1]-nas;  // vlastni motylek
	       f[m][l][i1]=f[m][l][i1]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }
   }

//<B> FOURIEROVA TRANSFORMACE PODEL OSY  Y

  //vypocet tabulky bitovì inverzních indexù
  for  (i=0;i<N2;i++)           // smycka i - projizdi vsechny hodnoty y
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m2;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m2-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N3;m++)            //smycka m - smycka projizdi hodnoty z
  for (l=0;l<N1;l++)          //smycka l - smycka projizdi hodnoty x
    {
   //1D-y pøeuspoøádání
     for  (i=0;i<N2;i++)           // smycka i - projizdi hodnoty y
       if(bitinv[i]>i)             //podmínka aby k prohození došlo jen 1x
        {nas=f[m][i][l];
         f[m][i][l]=f[m][bitinv[i]][l];	   //1D-y bitove preusporadani
         f[m][bitinv[i]][l]=nas;	      //1D-y bitove preusporadani
        }
  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  fft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  fft) v jedne dilci fft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci fft
  */
    for (k=1;k<N2;k<<=1)
      {
    	W=exp(-Iu*Pi/k); // komplexni  vektor W ..jadro dilci fft
	  		             // ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci fft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci fft
	*/

	for (j=0;j<N2;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;     //  inicializace dilci fft Wi=W**1;
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

        nas=f[m][i2][l];
	    f[m][i2][l]=f[m][i1][l]-nas;  // vlastni motylek pro i=0;
	    f[m][i1][l]=f[m][i1][l]+nas;

       // smycka i .. vypocet dilci ifft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;
	       nas=f[m][i2][l]*Wi;

	       f[m][i2][l]=f[m][i1][l]-nas;  // vlastni motylek
	       f[m][i1][l]=f[m][i1][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }

//<C> INVERZNÍ FOURIEROVA TRANSFORMACE PODEL OSY  Z

  //vypocet tabulky bitovì inverzních indexù
  for  (i=0;i<N3;i++)           // smycka i - projizdi vsechny hodnoty z
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m3;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m3-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N2;m++)            //smycka m - smycka projizdi hodnoty y
  for (l=0;l<N1;l++)          //smycka l - smycka projizdi hodnoty x
    {
      //1D-z bitovì inverzní pøeuspoøádání
     for  (i=0;i<N3;i++)           // smycka i - projizdi hodnoty y
       if(bitinv[i]>i)             //podmínka aby k prohození došlo jen 1x
        {nas=f[i][m][l];
         f[i][m][l]=f[bitinv[i]][m][l];	   //1D-y bitove preusporadani
         f[bitinv[i]][m][l]=nas;	      //1D-y bitove preusporadani
        }


  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  fft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  fft) v jedne dilci fft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci fft
  */
    for (k=1;k<N3;k<<=1)
      {
	W=exp(-Iu*Pi/k); // komplexni  vektor W ..jadro dilci fft
			         // ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci fft
	*/

	for (j=0;j<N3;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;     //  inicializace dilci fft Wi=W**1;
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

        nas=f[i2][m][l];
	    f[i2][m][l]=f[i1][m][l]-nas;  // vlastni motylek pro i=0;
	    f[i1][m][l]=f[i1][m][l]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;
	       nas=f[i2][m][l]*Wi;

	       f[i2][m][l]=f[i1][m][l]-nas;  // vlastni motylek
	       f[i1][m][l]=f[i1][m][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }


 //uvolneni pomocnych poli z pameti
 free(bitinv);
 return(0);		//fft probehla uspesne
};













//************************** INVERZNÍ ************************************
int ifft3(complex huge ***s,complex huge ***f,WORD m3,WORD m2,WORD  m1)
{
  WORD i,j,k,l,m;       // indexy smycek
  WORD i1,i2;         // indexy operandu v motylku
  WORD N1=1<<m1;      // x -ový rozmìr tìlesa
  WORD N2=1<<m2;      // y -ový rozmìr tìlesa
  WORD N3=1<<m3;      // z- ový rozmìr tìlesa
  WORD Nmax;		  //maximální rozmìr tìlesa
  unsigned long int D=N1*N2*N3;  // dìlitel  D=Nx*Ny*Nz 	ROZDíL PROTI FFT !!!

  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  ifft
  complex  Wi;                // i-ta mocnina vektoru W


  //complex huge *W;           //ukazatel na tabulku mocnin jádra ifft (index==mocnina)
  WORD *bitinv;	             //ukazatel na tabulku bitove inverznich indexù

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  Nmax=((Nmax=(N1>N2)? N1:N2)>N3)? Nmax:N3; //urèení maximálního rozmìru tìlesa
  if((bitinv=(WORD *)calloc(Nmax,sizeof(WORD)))==NULL) return(1); //chyba 1

  /*  if ((W=(complex huge*)farcalloc(Nmax,sizeof(complex)))==NULL)
                     {
					   farfree(fb);
                       free(bitinv);
                       return(2);//chyba 2
				     };                     */





  //<A> INVERZNí FOURIEROVA TRANSFORMACE PODEL OSY X

  //vypocet bitove inverzniho pole
  for  (i=0;i<N1;i++)       // smycka i - vsechny x ove souradnice
    {
     /// W[i]=exp(+Iu*i*Pi/k); // komplexni  vektor W ..jadro dilci ifft

      k=0;		                        //inicializace bitove inverzniho indexu
      for (j=0;j<m1;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m1-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N3;m++)             //smycka m - smycka projizdi vsechny z souøadnice
  for (l=0;l<N2;l++)           //smycka l - smycka projizdi vsechny y souøadnice
    {
   //1D-x bitovì inverzní pøeuspoøádání
     for  (i=0;i<N1;i++)                  // smycka i - projizdi vsechny x souøadnice
       f[m][l][i]=s[m][l][bitinv[i]]/D;  //bitove preusporadani l-teho radku
				                //a dìlení signálu Nx*Ny*Nz ROZDíL PROTI FFT !!!

  // algoritmus  TID-motylek -podel osy x
  // smycka  k .. etapa  ifft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  ifft) v jedne dilci ifft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci ifft
  */
    for (k=1;k<N1;k<<=1)
      {
			 //ROZDíL PROTI fft !!! ve znaménku exponentu
	 W=exp(+Iu*Pi/k); // komplexni  vektor W ..jadro dilci ifft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci ifft
	*/

	for (j=0;j<N1;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
  	    Wi=W;  //  inicializace dilci fft Wi=W**1
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

        nas=f[m][l][i2];
	    f[m][l][i2]=f[m][l][i1]-nas;  // vlastni motylek pro i=0;
	    f[m][l][i1]=f[m][l][i1]+nas;

       // smycka i .. vypocet dilci fft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;

	       nas=f[m][l][i2]*Wi;

	       f[m][l][i2]=f[m][l][i1]-nas;  // vlastni motylek
	       f[m][l][i1]=f[m][l][i1]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }
   }

//<B> INVERZNÍ FOURIEROVA TRANSFORMACE PODEL OSY  Y

  //vypocet tabulky bitovì inverzních indexù
  for  (i=0;i<N2;i++)           // smycka i - projizdi vsechny hodnoty y
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m2;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m2-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N3;m++)            //smycka m - smycka projizdi hodnoty z
  for (l=0;l<N1;l++)          //smycka l - smycka projizdi hodnoty x
    {
   //1D-y pøeuspoøádání
     for  (i=0;i<N2;i++)           // smycka i - projizdi hodnoty y
       if(bitinv[i]>i)             //podmínka aby k prohození došlo jen 1x
        {nas=f[m][i][l];
         f[m][i][l]=f[m][bitinv[i]][l];	   //1D-y bitove preusporadani
         f[m][bitinv[i]][l]=nas;	      //1D-y bitove preusporadani
        }

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  ifft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  ifft) v jedne dilci ifft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci ifft
  */
    for (k=1;k<N2;k<<=1)
      {	          	 // ROZDíL PROTI fft !!! - ve znaménku exponentu
	W=exp(+Iu*Pi/k); // komplexni  vektor W ..jadro dilci ifft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci ifft
	*/

	for (j=0;j<N2;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;     //  inicializace dilci fft Wi=W**1;
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku


        nas=f[m][i2][l];
	    f[m][i2][l]=f[m][i1][l]-nas;  // vlastni motylek pro i=0;
	    f[m][i1][l]=f[m][i1][l]+nas;

       // smycka i .. vypocet dilci ifft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;
	       nas=f[m][i2][l]*Wi;

	       f[m][i2][l]=f[m][i1][l]-nas;  // vlastni motylek
	       f[m][i1][l]=f[m][i1][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }

//<C> INVERZNÍ FOURIEROVA TRANSFORMACE PODEL OSY  Z

  //vypocet tabulky bitovì inverzních indexù
  for  (i=0;i<N3;i++)           // smycka i - projizdi vsechny hodnoty z
    {
      k=0;		    //inicializace bitove inverzniho indexu
      for (j=0;j<m3;j++)               //bitova inverze cisla i,j znamena cislo
      if ((1<<j)&i) k+=1<<(m3-1-j);    //prave  invertovaneho bitu
      bitinv[i]=k;		       //ulozeni bitove inverzni hodnoty indexu do pameti
    }

for (m=0;m<N2;m++)            //smycka m - smycka projizdi hodnoty y
  for (l=0;l<N1;l++)          //smycka l - smycka projizdi hodnoty x
    {
      //1D-z bitovì inverzní pøeuspoøádání
     for  (i=0;i<N3;i++)           // smycka i - projizdi hodnoty z
       if(bitinv[i]>i)             //podmínka aby k prohození došlo jen 1x
        {nas=f[i][m][l];
         f[i][m][l]=f[bitinv[i]][m][l];	   //1D-y bitove preusporadani
         f[bitinv[i]][m][l]=nas;	      //1D-y bitove preusporadani
        }

  // algoritmus  TID-motylek -podel radku
  // smycka  k .. etapa  ifft
  /* k ma vyznam poctu souctu(provedeni vypoctu podle
     zakladni formule  ifft) v jedne dilci ifft v dane etape
     tj. ma vlastne  vyznam  polovicky poctu vzorku v ramci
     dilci ifft
  */
    for (k=1;k<N3;k<<=1)
      {	          	 // ROZDíL PROTI fft !!! - ve znaménku exponentu
	W=exp(+Iu*Pi/k); // komplexni  vektor W ..jadro dilci ifft
			// ma byt W=exp(-Iu*2*Pi/(2*k))

	// smycka j .. provadi dilci ifft (v ramci  jedne etapy)
	/*  j ma vyznam adresy prvniho vzorku prerozdeleneho signalu
	    pro danou  dilci ifft
	*/

	for (j=0;j<N3;j+=2*k)
	  {
/*pozn mohl bych nahradit  j+=2*k vyrazem j+=k
 a skrtnout i1  a  nahradit jej j a j++ !!
 usetrim 1 presuv
*/
	    Wi=W;     //  inicializace dilci fft Wi=W**1;
	    i1=j;     //  index horniho operandu v  motylku
	    i2=j+k;   //  index dolniho operandu  v motylku

        nas=f[i2][m][l];
	    f[i2][m][l]=f[i1][m][l]-nas;  // vlastni motylek pro i=0;
	    f[i1][m][l]=f[i1][m][l]+nas;

       // smycka i .. vypocet dilci ifft
	    for(i=1;i<k;i++)
	      {
	       i1++;i2++;
	       nas=f[i2][m][l]*Wi;

	       f[i2][m][l]=f[i1][m][l]-nas;  // vlastni motylek
	       f[i1][m][l]=f[i1][m][l]+nas;

	       Wi=W*Wi;          // pootoceni vektoru

	      }
	  }
      }


   }



 //uvolneni pomocnych poli z pameti
 free(bitinv);
 return(0);		//ifft probehla uspesne
};






#endif





