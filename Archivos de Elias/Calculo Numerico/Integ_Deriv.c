#include <stdio.h>
/*Calcula la integral, de una funciona dada por datos experimentales
 en dos columnas, por trapecios
 calcula la dderivada por diferencias finitas */
main()
{ FILE *pfinp, *pfout;
 int i,j,n,nc,Nx,Ny,Ncabec,Ncol,icol,ifilas;
 int result;
 double  x[10000],y[10000],z[10000],der[10000];
 double var[50];
 double b1,b2, Sum, Dx,Dy;
 char cabecera[100];
 char filename[50];
 printf("Este programa calcula numéricamente la integral\n");
 printf("y la derivada de una función dada en un fichero\n");
 printf("de datos en varias columnas\n\n\n");
 printf("Se pregunta pos pantalla el numero de la columnas x e y\n");
 printf("y el número de filas de encabezamiento (ignoradas)\n\n\n");
 printf("No de las columnas x, y  y no total de columnas?  ");
 scanf("%i %i %i",&Nx,&Ny,&Ncol);
 printf("\n No. de Filas de encabezamiento (ignoradas)? ");
 scanf("%i",&Ncabec);
 printf("\nNombre del fichero, con extension:  "); scanf("%s",filename);

 pfinp=fopen(filename,"r"); //Fichero de datos
 //lee  lineas de cabecera
 for(ifilas=0;ifilas<Ncabec;ifilas++) 
 {i=-1;
    do 
    {i++;
    fscanf(pfinp,"%c", &cabecera[i]);
    printf("%c",cabecera[i]);
    } while(cabecera[i]!=10&&i<100);
    printf("\n");//getchar();
 }
 printf("Fin de la cabecera (pulsar <INTRO>/<RETURN>))\n");
 getchar(); //getchar();
  i=0;
 do
 {
 for(icol=1;icol<=Ncol;icol++) 
 { result=fscanf(pfinp,"%lf", &var[icol]) ;
  if(result==EOF) break;}
  if(result==EOF) break;
 x[i]=var[Nx];
 y[i]=var[Ny];
 
  //fscanf(pfinp,"%lf %lf %lf %lf",&b1,&b2,&x[i],&y[i]);
 printf("\n %lf %lf",x[i],y[i]);
 i++;
 } while(1);
 fclose(pfinp);
 n=i-1;
 fclose(pfinp);
 printf("\n leidos %i datos",n+1);
 printf("\n\n Pulsar <INTRO> /<RETURN> para calcular la integral y la derivada");
 getchar();
 pfout=fopen("Int_der.dat","w");
 z[0]=0.;
 Sum=0.; 
 for(i=1;i<n;i++)
 {
 Sum=Sum+y[i];	
 z[i]=z[i-1]+0.5*(y[i]+y[i-1])*(x[i]-x[i-1]);
 der[i] =(y[i+1]-y[i-1])/(x[i+1]-x[i-1]);
}
der[0]=(y[1]-y[0])/(x[1]-x[0]);
j=1;
do
{
Dx= x[n+j]-x[n-j];
Dy=y[n+j]-y[n-j];
j=j+1;
} while(Dx==0.);
der[n] =(y[n]-y[n-1])/(x[n]-x[n-1]);
z[n]=z[n-1]+0.5*(y[n]+y[n-1])*(x[n]-x[n-1]); 

// Escribe resultados
fprintf(pfout,"i    x            y    Int ydx     dy/dx");
for(i=0;i<=n;i++)
{ printf("\n%i  %lf %lf %lf %lf",i,x[i],y[i],z[i],der[i]);
fprintf(pfout,"\n%i  %lf %lf %lf %lf",i,x[i],y[i],z[i],der[i]);
}
Sum=Sum*(x[n]-x[0])/n; //(x[n]-x[0])/n = incremento medio de x 
printf("\n n: %i, Suma y(xi)*Dx: %lf",n,Sum);
fclose(pfout);
pfout=fopen("Int_der.plt","w");
fprintf(pfout,"plot 'Int_der.dat' using 2:3 with lines title 'data',\\");
fprintf(pfout,"\n     'Int_der.dat' using 2:4 with lines title 'integral',\\");
fprintf(pfout,"\n     'Int_der.dat' using 2:5 with lines title ' derivada'");
fclose(pfout);
 system("Int_der.plt");
}
