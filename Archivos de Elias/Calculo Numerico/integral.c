#include <stdio.h>
#include <math.h>
/* Resuelve numericamente la integral de una funcion */

double f(double x)
  /* función que hay que definir. 
    Como ejemplo resuelve la integral de -1 a 1 de sqrt(1-x*x) (semicircunferencia)
    que vale exactamente pi/2

    Es un ejemplo bastante patologico porque la derivada de f es infinita en los extremos
    y la discretización introduc grandes errores. 
   Aun así el método da buen resultado con muchas iteraciones */
{double pi=3.14159265358979323846;

 return sqrt(1-x*x);
 //return x*x*(1-sin(3*x))/2./pi;
 //return 5*x*x*x*x;
}
main()
{   double pi=3.14159265358979323846;
  double a=-1, b=1,err=1.e-6; //limites de integracion y error permitido
  double dint,oldint,x,dx;//integral, integral anterior, x, dx : variables mudas
  int n,i; // no. de intervalos e indice para designarlos
  printf("\n Resuelve una integral: ejemplo I = integral de -1 a 1  de sqrt(1-x^2) ");
  printf("\n resuelve la integral por trapecios");
  printf("\n Error maximo: %.2le",err);
  printf("\nNo. intervalos       integral");
  n=1;
  dint =(b-a)*(f(a)+f(b))/2.;
  do
  /* convergencia de la integral: en cada iteracion
     se duplica el no. de intervalos */
  {
    printf("\n%i \t%.16lf",n ,dint);
    n=2*n;
    dx = (b-a)/n;
    oldint=dint;
    dint =(f(a)+f(b))/2.;
    for(i=1;i<n;i++)
    {
      x = a+i*dx;
      dint=dint+f(x);
    }
    dint =dint*dx;
    
  } while(fabs(oldint-dint)>err);
  
  printf("\nConvergencia alcanzada: pulsa <RET>");
  getchar();

  /* Integracion por la regla de Simpson:
     la expresi¢n es la integral exacta de una parabola
     que coincide con la funcion
     en a, (a+b)/2 y b

     Se hace dividiendo el intervalo en un n£mero n de trozos */

    printf("\n integral por la regla de Simpson");
    dint =(b-a)*(f(a)+4*f((a+b)/2)+ f(b))/6.;
  n=1;
  do
  /* convergencia de la integral: en cada iteracion
     se duplica el no. de intervalos */
  {
    printf("\n%i \t%.16lf",n ,dint);
    n=2*n;
    dx = (b-a)/2/n;
    oldint=dint;
    dint = f(a);
   for(i=1;i<=n;i++)   dint=dint+4*f(a+(2*i-1)*dx)+2*f(a+2*i*dx);

    dint =(dint-f(b))*dx/3;
    
  } while(fabs(oldint-dint) > err);
  
  printf("\nConvergencia alcanzada: pulsa <RET>");
  printf("\n pi/2 = %.16lf",pi/2.);
  getchar();


}
