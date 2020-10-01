INSTRUCCIONES DEL PROGRAMA integ_deriv
1) Este programa calcula la integral y la derivada
de una función dada por datos experimentales en un fichero de 
dos o más columnas llamado "FdO.dat":  
x, y,  y otras variables que no se usan.
El fichero debe ir SIN ENCABEZAMIENTOS y según como sea hay que modificar la linea 15:

 fscanf(pfinp,"%lf %lf %lf %lf",&x[i],&y[i],&var[1],&var[2]);

donde las variables var no se usan y están puestas sólo para leer ficheros con más
de dos columnas. En el ejemplo el fichero "FdO.dat" contiene los valores de x, |F|^2, Fr y Fi
que son los valores de x y de una función de onda calculada por el método de Euler, siendo

Fr la parte real, Fi la parte imaginaria y |F|^2 el módulo al cuadrado, que es lo que se
integra en el ejemplo y da 1, ya que estaba normalizada.

LOS RESULTADOS SON 

z[i] = integral desde x[0] a x[i] de y[i]*dx
der[i] = dy/dx cal culada en x[i]

Por ejemplo, para calcular el valor esperado de x, 
en el programa hay que hacer que z sea:

(linea 30)

z[j] = z[j-1] + 0.5 (x[j]*y[j]+x[j-1]*y[j-1])*(x[i]-x[i-1])

es decir el integrando es xy en vez de y.

2) Los resultados los guarda en el fichero "Int_der.dat". También crea el script
"Int_der.plt" para dibujarlos con GNUPLOT.

3) Normalmente, y si sólo hay que hacerlo una vez, ES PREFERIBLE USAR OTROS PROGRAMAS
usuales: Origin, SciDavies, Kaleida_graph, etc.
Este puede ser útil si hay que hacerlo con muchos ficheros, modificándolo
para que iterativamente abra cada vez uno y guarde los resultados con nombres distintos, etc. 

Otra utilidad es incluirlo como función (que no se llame main), en otros programas de 
cálculo que necesitan obtener la integral o la derivada. O simplemente añadiendo las lineas
correspondientes al programa.

4) El ALGORITMO empleado es muy simple. Para la integral la regla del trapecio. Los datos
son x[i],y[i]  y  si los puntos están numerados de 0 a n (el programa los numera automáticamente), la integral se calcula como:

Integral de x[0] a x[j] = z[j] = 
                     Suma (de i = 1 a j) 0.5*(y[i]+y[i-1])(x[i]-x[i-1])

La derivada, se llama 

der[i] = (y[i+1]-y[i-1])/(x[i+1]-x[i-1])

excepto si x[i-1]=x[i+1] (es decir, si hay varios puntos con la misma x y diferente y
porque son medidas distintas con errores experimentales). En ese caso se hace la diferencia
finita y[i+2]-y[i-2], o con mayor incremento si es necesario, y la correspondiente de x.

En los extremos se hace la diferencia finita lateral:
der[0] = (y[1]-y[0])/(x[1]-x[0])
der[n] = (y[n]-y[n-1])/(x[n]-x[n-1])

5) Este algoritmo es el que emplean los programas standard citados, y funciona bien cuando
los datos son calculados pero es MUY PELIGROSO 
SI SE TRATA DE DATOS EXPERIMENTALES CON RUIDO. En ese caso a pequeñas diferencias en x
corresponden diferencias en y prácticamente aleatorias, por lo que la derivada no debe
calcularse así, ya que saldría un valor al azar en cada punto.
Hay otros algoritmos más sofisticados que suavizan los datos.

Elías Palacios