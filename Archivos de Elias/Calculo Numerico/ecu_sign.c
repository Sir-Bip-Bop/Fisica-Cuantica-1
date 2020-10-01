#include <stdio.h>
#include <math.h>
/* Resuelve la ecuacion exp(-x)=x  por el metodo de biseccon */


double funcion(double x) 
{return(exp(-x)-x);}
main()
{
  double a=-1000.,b=1000.,c,err=1.e-8;
  int n=0;
  printf("\n No de iteraciones   Solucion");
  while(fabs(b-a)>err)
  {
  n++;
  c=(a+b)/2;

    if(funcion(c)*funcion(a)<0) b=c;

//  if((exp(-a)-a)*(exp(-c)-c)<0) b=c;
  else a=c;
  printf("\n %d \t\t%.10lf",n,c);
  }
printf("\n Covergencia alcanzada. Pulsar <RET>");
getchar();
}
