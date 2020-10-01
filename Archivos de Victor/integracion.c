#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define f(x) sin(x)

int main(int argc,char **argv){
    double integral,delta,posicion_x,x_inicial,x_final;
    int i,j,N;
    FILE *f;
    char nomb[30];
    switch(argc){ //Tratamiento de datos por ventana de comandos (terminal)
        case 1:
            strcpy(nomb,"output_integracion.txt");
            x_inicial=0;
            x_final=2.0*asin(1.0);
            N=1000;
        break;
        case 2:
            strcpy(nomb,argv[1]);
            if(strcmp("help",nomb)==0){
                printf("Hay varias maneras de ejecutar este programa:\n>%s\n>%s nombre_fichero_salida\n>%s nombre_fichero_salida x_inicialnicial x_finalinal\n>%s nombre_fichero_salida x_inicialnicial x_finalinal N\n",argv[0],argv[0],argv[0],argv[0]);
                exit(1);
            }
            x_inicial=0;
            x_final=2.0*asin(1.0);
            N=1000;
        break;
        case 4:
            strcpy(nomb,argv[1]);
            x_inicial=atof(argv[2]);
            x_final=atof(argv[3]);
            //Revisar si aqui hace falta meter la condicion de que sean iguales
            N=1000;
        break;
        case 5:
            strcpy(nomb,argv[1]);
            x_inicial=atof(argv[2]);
            x_final=atof(argv[3]);
            //Revisar si aqui hace falta meter la condicion de que sean iguales
            N=atoi(argv[4]);
        break;
        default:
            printf("Error: input incorrecto.\nHay varias maneras de ejecutar este programa:\n>%s\n>%s nombre_fichero_salida\n>%s nombre_fichero_salida x_inicialnicial x_finalinal\n>%s nombre_fichero_salida x_inicialnicial x_finalinal N\n",argv[0],argv[0],argv[0],argv[0]);
            exit(2);
    }
    f=fopen(nomb,"wt");
    if(f==NULL){
        printf("Error con el fichero de salida.");
        exit(3);
    }
    for(i=2;i<(N+1);i++){
        delta=(x_final-x_inicial)/i;
        for(j=0,integral=0,posicion_x=x_inicial+delta/2;j<i;j++){
            integral+=f(posicion_x);
            posicion_x+=delta;
        }
        integral*=delta;
        fprintf(f,"%d %lf\n",i,integral);
    }
    fclose(f);
    char plot[35]="plot_";
    f=fopen(strcat(plot,nomb),"wt");
    if(f==NULL){
        printf("Error con el fichero de GNUPLOT.");
        exit(4);
    }
    else{
        fprintf(f,"set xlabel \"N\"\nset ylabel \"Valor de la integral\"\nf(x)=2\nplot \"%s\" w l t \" Numerico\", f(x)  t \" Teorico\"",nomb);
    }
    fclose(f);
    return 0;
}
