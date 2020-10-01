# Archivos de Unai Lería
Para más información sobre los archivos en esta carpeta busque el archivo en [Archivos](#archivos).

# Archivos
- [Creador de librerias de lectura](leer%datos_creador%de%libreria/)
  - [input_reader_creator.py](#creador-de-librerias-de-lectura-de-datos)


## Creador de librerias de lectura de datos
> Este script de Python solo soporta (actualmente) lectura de tipos int, double y char
> 
Pasos para crear una librería:
1) Ejecutar el código:
   ```bash
   $python input_reader_creator.py
   ```
2) Seguir los pasos:
   1) Escribir nombre de la nueva libreria.
   2) Escribir nombre del nuevo Struct con los datos que se leeran.
   3) Escribir cada una de las variables en el siguiente formato:
        ``` 
        tipo nombre_variable descripcion
        ```
        La descripción no es necesario. Pero se aconseja.

    4) Escribir el nombre de la función que se llamará desde otros códigos.

Para utilizar la librería creada deberá introducir en su código lo siguiente:
```c
#include "nombre_libreria_header.c"
nombre_struct foo;
nombre_funcion(&foo);
``` 
Así tendrás en la variable ```foo``` de tipo ```nombre_struct``` los valores leídos del fichero ```nombre_libreria_config.txt```.

# Qué puñetas es foo y por qué está en todas partes?
> https://www.webopedia.com/TERM/F/foobar.html
De nada
    
