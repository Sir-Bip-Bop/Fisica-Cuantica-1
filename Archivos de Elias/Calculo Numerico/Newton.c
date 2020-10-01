#include <stdio.h>
#include <math.h>
//resuelve una ecuacion f(x)=0 por el metodo de Newton
// Ejemplo exp(-x)-x = 0

double f(double x)// Define funcion
{
return exp(-x)-x;
}
double fp(double x) //Define la derivada
{

return -exp(-x)-1.;
}

main()
{
double x0,x1,epsilon;
printf("\n dar prueba inicial y error: ");
scanf("%lf%lf",&x1,&epsilon);
do
  {
    x0=x1;
    //escribe cada vez x1 para ver lo que va saliendo
    x1= x0 -f(x0)/fp(x0);// calcula un nuevo x1
    printf("\n %.10lf",x1);
  }
while(fabs(x1-x0) >= epsilon);
printf("\n Convergencia alcanzada. Pulsar <RET>");
getchar();
}
