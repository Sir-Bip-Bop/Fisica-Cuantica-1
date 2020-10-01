# include <stdlib.h>
# include <stdio.h>
# include <time.h>

//# include "eispack.h"
#include "eispack.c"
//Resuelve la ec de Schrodinger unidimensional para un pozo cuadrado
// de  potencial  1D (a, b) en metros: paredes
// V0: profundidad en eV.

//variables globales 
int nf=0; //funcion de onda para listar, 0 = fundamental
double pi=3.14159265358979323846; //número pi
double qe=1.60219; // carga del electron sin exponente (x 10^-19)
double h = 1.05459; //h barra (x10^-34) OJO:  no es h
double uma=1.66053; // uma en kg (x10^-27)
double muma = 1.; // masa en uma. 1 = aprox masa proton
double m; // masa en kg
double a=-0.5,b=0.5; //Pozo cuadrado de profundidad V0
double aa; //anchura del pozo en Angstrom
double V0 = 1.0; // profundidad del pozo en eV
double V(double x)
// Funcion potencial  en eV Se toma el mínimo como cero
//retorna 2mV(x)/h^2
{    
     if(x>=a&&x<=b) return 0;// Pozo cuadrado  de profundidad V0 en eV.
     else return V0; 
 
/* Incluir la definicion para otro potencial.*/
}
main()
{/* Metodo de diferencias finitas.
    Sea la funcion de onda F(x)
    y la Ec. de Schrodinger 1d: [-h^2/m d^2/dx^2-V(x)]F(x)=EF(x)
    Se aproxima  d^2F/dx^2 = (Fi+1+Fi-1-2*Fi)/Dx^2
    Definiendo alpha(x) = (2*m*Dx^2/h^2)*V(x) y lambda = (2*m*Dx^2/h^2)*E
    Se cumple la ecuacion en diferencias finitas:
    (2+alpha(x_i))*Fi -Fi+1-Fi-1 =lambda*Fi
    Considerando las Fi como componentes de un vector, 
    es una ecuación de autovalores y autovectores.
    
    Se resuelve numéricamente usando el paquete libre eispack (de GNU) que
    obtiene los autovalores y autovectores (valores de la autofuncion para cada
    autovalor)
    Se supone que el potencial debe ser muy alto excepto para x1 < x < x2.
    unico rango de valores con F ditinta de cero. 
  */  
FILE * pfileout;
FILE * pfileout2;
FILE * pfileout3;
 int n=1001,err,i,j,ilist=51; double *d,*e,*z;
 int ia,ib; //puntos del borde del pozo
 double xmed,x2med,P2med;
 double x,Dx; // punto x generico y espaciado en metros entre puntos para calcular la funcion de onda
 double Potencial,Vmax,Vmin;
 double EeV,EdivE0,EinfeV,E1infeV;
 double k,k0a,ro;
 double u1,u2,u,v; //Para calcular energia analiticamente
 double zteo;
 double x1,x2,xi; //limites de x para calcular: se ha tomado el doble de la anchura del pozo dada
 double Norma,Phi2_max;
 double gamma; // 2 m qe/h/h (eV/A^2)
 m=muma*uma*1.e-27; //masa en kg
 aa=b-a; // anchura del pozo en angstroms
 if(n<ilist) ilist=n;
 gamma = 2*muma*uma*qe/h/h*1.e2;  // 2 m qe/h^2 en 1/(eV*A^2) 
 pfileout=fopen("Schr_pozo.txt","w");
 
 /* Límites de x para calcular la FdO
 la mitad de los puntos dentro del pozo y la mitad fuera */
 Dx=2*(b-a)/(n-1);  //Intervalo Delta x
 x1=a-(n-1)/4*Dx;
 x2=b+(n-1)/4*Dx;
 ia=floor((a-x1)/Dx);
 ib=ceil((b-x1)/Dx);
 printf("\n Datos del calculo:");
 printf("\n Potencial: pozo cuadrado 1D ");
 fprintf(pfileout,"\n Datos del calculo:");
 
 printf(" POZO CUADRADO");fprintf(pfileout," POZO CUADRADO");
 printf("\n m =%10le kg = %5.3lf  uma,h = %le (hbarra)",m,muma,h*1.e-34);
 fprintf(pfileout,"\n m =%10le kg = %5.3lf uma",m,muma);
 printf("\n Paredes del pozo cuadrado: %lf %lf angstrom",a,b);
 fprintf(pfileout,"\n Paredes del pozo cuadrado: %lf %lf angstrom",a,b);
 printf("\n altura de las paredes %lf eV",V0) ;
 fprintf(pfileout,"\n altura de las paredes %lf eV",V0) ;    
 printf("\n Dx: %lf A, no. de puntos calculados de Fi: %i",Dx,n); 
 fprintf(pfileout,"\n Dx: %lf A, no. de puntos calculados de Fi: %i",Dx,n);
 printf("\n Lista la función de ona número: %i",nf );
 fprintf(pfileout,"\n Lista la función de ona número: %i",nf );
 printf("\n Extremos del calculo: %lf, %lf A ",x1,x2 );
 printf("\n la F. de O. se hace cero (V => infinito) en los extremos");
 fprintf(pfileout,"\n Extremos del calculo: %lf, %lf A ",x1,x2 );
 fprintf(pfileout,"\n la F. de O. se hace cero (V => infinito) en los extremos");

 printf("\nteclear <RET>");
 getchar();//para que no se cierre la ventana
// Determina maximo y miniomo del potencial para escalar el dibujo
 Vmax=-1.e8;
 Vmin=1.e8;
 for(i=0;i<=n;i++)
 {
 if(Vmax<V(Dx*i)) Vmax=V(Dx*i);
 if(Vmin>V(Dx*i)) Vmin=V(Dx*i);
 }
 /* Variables para la funcion de diagonalizacion
    de una matriz simetrica tridiagonal
 d = entrada: diagonal mayor de la matriz 2+alpha[i]
       salida: vector de autovalores
 e = diagonales superior e inferior
  en este problema e[i]=-1, e[0] no se usa
 z= matriz Para convertir matriz simétrica en tridiagonal. 
  Para tridiagonal (es el caso) z no se usa y se da la matriz identidad listada por filas.
*/
// 
 d = ( double * ) malloc ( n* sizeof ( double ) );
 e = ( double * ) malloc ( n* sizeof ( double ) );
 z = ( double * ) malloc ( n*n* sizeof ( double ) );
 /* ejemplo diagonalizacion
 for(i=0;i<n;i++)
 {
 for(j=0;j<n;j++)z[i+n*j]=0.;
 d[i]=2.; 
 e[i]=-1.;
 z[i+n*i]=1.;
  }
  */
  printf("\n Lista algunos valores de la diagonal:2+ 2*m*Vi*Dx^2/h^2");
  printf("\nNum  2+alpha     x[i](A)    vi      eV");
  printf("\n=================================================");
  fprintf(pfileout,"\n Lista algunos valores de la diagonal:2+ 2*m*Vi*Dx^2/h^2");
  fprintf(pfileout,"\nNum  2+alpha     x[i](A)     vi      eV");
  fprintf(pfileout,"\n=================================================");
  for(i=0;i<n*n;i++)z[i]=0.;
 for(i=0;i<n;i++)
 {
 xi =x1+i*Dx; 
 for(j=0;j<n;j++)z[i+n*j]=0.;
 d[i]=2.+V(xi)*Dx*Dx*gamma;   // los valores de la diagonal 2+ vi =2+ V(xi)*2m*Dx^2/h^2 
 e[i]=-1.;
 /* z[] matriz identidad n x n. Listada por filas
  En este programa sólo  lista los autovalores y un autovector
 */
 z[i+n*i]=1.; 
 EeV=V(xi);
 if(!(i%((n-1)/10))) //Lista solo uno de cada 100 valores de las vi
 {
 printf("\n %i %10lf %10le %le %lf",i,d[i],xi,V(xi)*Dx*Dx*gamma,EeV);
 fprintf(pfileout,"\n %i %10lf %10le %le %lf",i,d[i],xi,V(xi)*Dx*Dx*gamma,EeV);
 }
/* if(i%100==0) //para listar con pausa cada 100 lineas
   {
    printf(" teclear <RET>");
    getchar();
   }
*/
  }
 printf("\n\n Diagonalizando...");
 
 err=tql2(n,d,e,z);
 printf("diagonalizacion finalizada");
 printf("\n\n Lista %i primeros AUTOVALORES Y ENERGIAS",ilist);
printf("\n Teclear <RET> para continuar");
 getchar();
 printf("\nn  lambda_n    En(eV)   E pozo inf(eV)   E/E0");
 fprintf(pfileout,"\n Lista %i primeros AUTOVALORES Y ENERIAS",ilist);
 fprintf(pfileout,"\nn  lambda_n    En(eV)    E pozo inf(eV)      E/E0");
 for(i=0;i<ilist;i++) 
 {
 EeV=d[i]/Dx/Dx/gamma;
 EdivE0=d[i]/d[0];
 //Energías para el pozo infinito en eV (calculo analitico para comparar)
 E1infeV=pi*pi/2.*h*h/muma/aa/aa/qe/uma*1.e-2; //Nivel fundamental 
 EinfeV= E1infeV*(i+1)*(i+1); //Otros niveles
 printf("\n%i %10lf %10lf %10lf %10lf",i,d[i],EeV,EinfeV,EdivE0);
 fprintf(pfileout,"\n%i %10lf %10lf %10lf %10lf",i,d[i],EeV,EinfeV,EdivE0);
}
 //Funcion de onda no. nf (elegida arriba)
 // Hay n calculadas, que se pueden listar y/o guardar poniendo un for aqui
 //Calcula la norma de la F. de. O no nf: integral trapecio
 Norma=0;
 Phi2_max=0.; // Valor maximo del cuadrado
 for(i=0;i<n;i++) 
 { Norma=Norma+z[i+nf*n]*z[i+nf*n];
   if(Phi2_max<z[i+nf*n]*z[i+nf*n]) Phi2_max=z[i+nf*n]*z[i+nf*n];
 }
 Norma=sqrt(Dx*(Norma-(z[0+nf*n]*z[0+nf*n]+z[n-1+nf*n]*z[n-1+nf*n])/2.));
 if(z[ia+nf*n]<0) Norma = -Norma;  //Elige el signo para que F(a) >0
 Phi2_max = Phi2_max/Norma/Norma;
 for(i=0;i<n;i++) z[i+nf*n]=z[i+nf*n]/Norma;
 //Calcula <x>, Delta x, <P^2> = (Delta P)^2
 xmed=0.;
 x2med=0.;
 P2med=0.;
 for(i=1;i<=n-2;i++)
 {x=x1+i*Dx;
 xmed=xmed+x*z[i+nf*n]*z[i+nf*n]*Dx;
 x2med=x2med+x*x*z[i+nf*n]*z[i+nf*n]*Dx;
 P2med=P2med+(z[i+1+nf*n]-z[i-1+nf*n])*(z[i+1+nf*n]-z[i-1+nf*n])/4./Dx;
 }
 
printf("\n <x> = %lf",xmed);
printf("\n <x2> = %lf, Delta x = %lf ",x2med,sqrt(x2med-xmed*xmed));
printf("\n <P2> = %lf, Delta p = %lf, Delta x * Delta p = %lf*hbarra",P2med, sqrt(P2med),sqrt(x2med-xmed*xmed)*sqrt(P2med));
printf("\n pulsar una tecla");
getchar();



 printf("\n\n\n Teclear <RET> para listar funcion de onda No %i",nf);
 getchar();
 printf("\n\n no punto Fi(x_I)       Fi_analitica");
 fprintf(pfileout,"\n\n no punto Fi(x_I)       Fi_analitica"); 

 
 pfileout2=fopen("Schr_pozo_FdO.txt","w");
 fprintf(pfileout2,"#_no punto Fi(x_I)  Fi_Vinf, analitica  Potencial(escalado)"); 
//for(i=0;i<n;i+=(n-1)/100) // para listar uno cada 100 puntos
for(i=0;i<n;i++)
 {
 // Lista funcion de onda analitica para el pozo de profundidad infinita
 
  // Pozo cuadrado infinito. funcion de onda analitica para nivel nf
  x=(i-n/4.)*Dx+a;
 if(x>=a&&x<=b) zteo=sqrt(2./(b-a))*sin((nf+1)*pi*(x-a)/(b-a)); 
 else zteo=0.;
 //Pozo cuadrado de profundidad V0 f.d.o. fundamental. Calculo analitico
/* En construccion:
  // k se obtiene de la ec. cos(ka/2)=k/k0, CT 47-a
 k0a=sqrt(2*m*V0*qe/h/h)*(b-a);
 //biseccion para acotar
 u1=0; //u= k*a/2
 u2=pi/2.;
 while(u2-u1>1.e-3)
 {u=(u1+u2)/2.;
 v=2*u/k0a;
 if(cos(u)-v>=0) u1=u;
 else u2=u;
 } 
 //Newton para precisar
 for(j=1;j<10;j++) u=u+(cos(u)-v)/(sin(u)-2/k0a);
 //f.d.o. analitica
 roa=sqrt(k0a*k0a-4*u*u);  // ro*aa
 xa=(i*Dx-(a+b)/2/(b-a);  // x/aa respecto del centro del pozo
 zteo=
 //etc...
 */
 //Normaliza la F. de O. Elige el signo para que F(a) >0
 
 printf("\n %5i\t%lf\t%lf",i,z[i+nf*n],zteo);
 fprintf(pfileout,"\n %5i\t%lf\t%lf",i,z[i+nf*n],zteo);
 Potencial=(V(x)-Vmin)/(Vmax-Vmin)*sqrt(Phi2_max); //Escala el potencial para dibujarlo con la F. d. O.
  fprintf(pfileout2,"\n %lf\t%lf\t%lf\t%lf",x,z[i+nf*n],zteo,V(x));
 } 
  
 free ( d );
 free ( e );
 free ( z );
fclose(pfileout); 
fclose(pfileout2); 
 printf("\n Energias en Schr_pozo.txt\n Funcion de onda no %d en  Schr_pozo_FdO.txt",nf);
 
 // genera el script de gnuplot para dibujar
 //
 pfileout3=fopen("Plot_Schr_pozo.plt","w");
 fprintf(pfileout3,"set ytics nomirror");
 fprintf(pfileout3,"\nset y2tics");
 fprintf(pfileout3,"\nset xrange [%lf:%lf]",x1,x2); 
 fprintf(pfileout3,"\nset yrange [%lf:%lf]",-sqrt(Phi2_max)*1.1,sqrt(Phi2_max)*1.1);
 fprintf(pfileout3,"\nset y2range [%lf:%lf]",Vmin-(Vmax-Vmin)*0.1,Vmax+(Vmax-Vmin)*0.1);
 fprintf(pfileout3,"\nset xlabel 'x(A)' ");
 fprintf(pfileout3,"\nset ylabel 'F(x) A-1' ");
 fprintf(pfileout3,"\nset y2label 'V(x) eV' ");
 fprintf(pfileout3,"\nplot 'Schr_pozo_FdO.txt' using 1:2 axes x1y1 with lines lt 7 title 'F(x) A-1',%c",92);
 fprintf(pfileout3,"\n     'Schr_pozo_FdO.txt' using 1:3 axes x1y1 with lines lt 3 title 'F(x) pozo infinito',%c",92);
 fprintf(pfileout3,"\n     'Schr_pozo_FdO.txt' using 1:4 axes x1y2 with lines lt 1 title 'V(x) eV)'");
 fclose(pfileout3);
 
 //Ejecuta el script de Gnuplot
 
 system("Plot_Schr_pozo.plt");
 printf("\n Teclear <RET> para terminar");
 getchar();
} 
     
