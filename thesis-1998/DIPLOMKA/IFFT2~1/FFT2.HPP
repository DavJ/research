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
int fft2(double huge **s,complex huge **f,unsigned int  m1,unsigned int m2)
{
  unsigned int i,j,k,l;       // indexy smycek
  unsigned int i1,i2;         // indexy operandu v motylku
  unsigned int N1=1<<m1;      // pocet radek matice obrazu
  unsigned int N2=1<<m2;      // pocet sloupcu matice obrazu
  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  fft
  complex  Wi;                // i-ta mocnina vektoru W

  complex huge **fm;               //ukazatel na pole mezivysledku fft(po 1D fft podle radek)
  unsigned int *bitinv;	      // ukazatel na pole bitove inverznich indexu

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  if((bitinv=(unsigned int *)calloc((N1>N2)?N1:N2,sizeof(int)))==NULL) return(1); //chyba 1
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







int ifft2(complex huge **s,complex huge **f,unsigned int  m1,unsigned int m2)
{
  unsigned int i,j,k,l;       // indexy smycek
  unsigned int i1,i2;         // indexy operandu v motylku
  unsigned int N1=1<<m1;      // pocet radek matice obrazu
  unsigned int N2=1<<m2;      // pocet sloupcu matice obrazu
  unsigned long int D=N1*N2;  // dìlitel  D=Nx*Ny	ROZDíL PROTI FFT !!!
  complex  nas;               // ulozeni  mezivysledku nasobeni aj.
  complex  W;                 // komplexni  vektor W ..jadro  ifft
  complex  Wi;                // i-ta mocnina vektoru W

  complex huge **fm;               //ukazatel na pole mezivysledku ifft(po 1D ifft podle radek)
  unsigned int *bitinv;	      // ukazatel na pole bitove inverznich indexu

//ALOKACE POMOCNYCH POLI (pro urychleni vypoctu)
  if((bitinv=(unsigned int *)calloc((N1>N2)?N1:N2,sizeof(int)))==NULL) return(1); //chyba 1
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










