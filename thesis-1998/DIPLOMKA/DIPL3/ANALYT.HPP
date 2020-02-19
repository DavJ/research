#ifndef  _analytical
#define  _analytical

#include <math.h>
#include <complex.h>
#include <alloc.h>
#include "const.cpp"


complex j=complex(0,1);
complex j23=pow((complex)(-1),2.0/3.0);
#define  third  1.0/3.0


/*
analytické øešení Blochových rovnic v rotující soustavì
pøi nulovém buzení
*/

void solut0(SPACE *M,double t,SPACE Mp,
	      double T1, double T2, double M0,double dB0)
{
  double arg,co,si,ex;

 /* dw=GamaH*dB0;tau=dw*t;*/

    arg=GamaH*dB0*t;
    co=cos(arg);si=sin(arg);ex=exp(-t/T2);
   /*dùležité poøadí výpoètù aby se nepøepsaly Mp nebo tau !
     je to proto,aby bylo možno funkci volat tak že se nové
     podmínky uloží na místo pùvodních */
  	M->z=(Mp.z-M0)*exp(-t/T1)+M0; //+M.z;
    arg=Mp.x;                     //uložení poèáteèní podmínky do arg
	M->x=(arg*co+Mp.y*si)*ex;     //+M.x;
	M->y=(Mp.y*co-arg*si)*ex;     //+M.y;
}


void roots(complex& a,complex& b,complex& s,double alpha,double beta,double delta)
{

double fi,theta;
complex ep,em,x,y;

#define deltaSQ delta*delta

theta=alpha-beta;

x=theta*(9-2*theta*theta-18*deltaSQ)/54;
theta=theta*theta;       /*nahradim kvadratem !*/
y=sqrt(27*(4*pow((deltaSQ+1),3)+theta*(4*deltaSQ*(2*deltaSQ+theta-5)-1)))/54;

fi=((deltaSQ+1)*3-theta)/9;
#undef deltaSQ

a=pow(x+y,third);b=pow(y-x,third);

if (fi<0){b=b*j23;};

ep=a+b;em=a-b;

a=-(third)*(alpha+2*beta);
b=a-em/2;
a=a+em;
s=sqrt(3)/2*ep;

}


/*
analytické øešení Blochových rovnic v rotující soustavì
pøi nenulovém buzení
*/



void solut1R(SPACE *Mk,double t,SPACE Mp,
	      double T1, double T2, double M0,double B1,double dB0)
{

SPACE   w0;
double w1,alpha,beta,delta,x;
complex a,b,s,COS,SIN;
complex A[3],B[3],C[3],D[3];

w1=GamaH*B1;
alpha=1/w1/T1;
beta=1/w1/T2;
delta=dB0/B1;

#define u0 w0.x
#define v0 w0.y
#define m0 w0.z


u0=Mp.x/M0;	//*pocatecni podminky normovaneho reseni*/
v0=-Mp.y/M0;
m0=Mp.z/M0;

/* calculate steady-state solution constants*/
#define multip x
#define deltakv (delta*delta)

multip=alpha/(alpha*(beta*beta+delta*delta)+beta);

D[0]=delta*multip;
D[1]=-beta*multip;
D[2]=(deltakv+beta*beta)*multip;

#undef multip
#undef deltakv
roots(a,b,s,alpha,beta,delta);

/* calculate other (transient) constants */
#define gama COS
#define deltaSQ (delta*delta)
gama=a*(pow((b-a),2)+pow(s,2));

A[0]=(a*u0*(1+(alpha-a)*(beta-a))-delta*alpha*(1+v0*a)+delta*a*(m0+a*v0))/gama;
A[1]=(a*u0*delta*(alpha-a)+a*v0*(alpha-a)*(beta-a)-(m0*a-alpha)*(beta-a))/gama;
A[2]=(a*u0*delta+a*v0*(beta-a)-(m0*a-alpha)*(pow((beta-a),2)+deltaSQ))/gama;

#undef gama
#undef deltaSQ

B[0]=u0-A[0]-D[0];
B[1]=v0-A[1]-D[1];
B[2]=m0-A[2]-D[2];


C[0]=-(beta*u0+delta*v0);
C[1]=delta*u0-m0-beta*v0;
C[2]=v0+alpha*(1-m0);

C[0]+=a*A[0]+b*B[0];
C[1]+=a*A[1]+b*B[1];
C[2]+=a*A[2]+b*B[2];


#define EXPA a
#define EXPB b
#define TAU  w1

 TAU=-w1*t;
 COS=cos(s*TAU);SIN=sin(s*TAU);EXPA=exp(-a*TAU);EXPB=exp(-b*TAU);

 Mk->x=M0*real((A[0]*EXPA+(B[0]*COS+C[0]/s*SIN)*EXPB+D[0]));
 Mk->y=-M0*real((A[1]*EXPA+(B[1]*COS+C[1]/s*SIN)*EXPB+D[1]));
 Mk->z= M0*real((A[2]*EXPA+(B[2]*COS+C[2]/s*SIN)*EXPB+D[2]));

  //pozor! zde asi neni zcela dobre jde o to zda je Mp  skutecne realne i pro
  //komplexni hodnoty a,b,s ktere se mohou vypoctem objevit--->NUTNO OVERIT !!!

#undef EXPA
#undef EXPB
#undef TAU
}

#undef third



//navzorkuje Ns  vzorkù komplexního signálu Mxy,s vzorkovací periodou Ts

void AddSignal0(complex *Mxy,double Ts,WORD Ns,SPACE Mp,double T2,double dB0)
{
  double t;
  WORD n;
  for (n=0;n<Ns;n++)
    {
      t=n*Ts;
      Mxy[n]+=complex(Mp.x,Mp.y)*exp(complex(0,-GamaH*dB0*t))*exp(-t/T2);
    }
}

#endif
