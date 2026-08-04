_Este proyecto ha sido creado como parte del currículo de 42 por andrcarr._

# get_next_line

## Descripción

`get_next_line` implementa una función en C que devuelve una línea cada vez
desde un descriptor de archivo. La línea devuelta incluye el carácter de salto
de línea (`\n`) cuando está presente. Cuando no quedan más datos por leer o se
produce un error, la función devuelve `NULL`.

El objetivo principal del proyecto es aprender a trabajar con descriptores de
archivo, la función `read`, variables estáticas y memoria dinámica.

Prototipo de la función:

```c
char *get_next_line(int fd);
```

## Instrucciones

Los archivos que forman la parte obligatoria son:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

Para compilar el proyecto junto con un archivo de prueba `main.c`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

El valor de `BUFFER_SIZE` puede modificarse durante la compilación:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

Para ejecutar el programa de prueba:

```sh
./gnl archivo.txt
```

El archivo `main.c` se utiliza únicamente para realizar pruebas y no forma
parte de la entrega.

## Algoritmo y justificación

La función utiliza un puntero estático llamado `stash`. Este puntero conserva
entre llamadas los caracteres que ya se han leído, pero que todavía no se han
devuelto como parte de una línea.

El algoritmo se divide en tres etapas:

1. **Lectura y acumulación:** si `stash` todavía no contiene un salto de línea,
   se leen bloques de hasta `BUFFER_SIZE` bytes. Cada bloque se añade a
   `stash`. La lectura se detiene cuando aparece `\n`, se alcanza el final del
   archivo o se produce un error.
2. **Extracción de la línea:** se copia desde el comienzo de `stash` hasta el
   primer `\n` incluido. Si el archivo termina sin `\n`, se copia todo el
   contenido restante.
3. **Actualización del estado:** la parte situada después de la línea devuelta
   se guarda en un nuevo `stash` para la próxima llamada. Si no queda contenido,
   se libera `stash` y pasa a valer `NULL`.

Se eligió una variable estática porque una variable local normal desaparecería
al terminar cada llamada y se perderían los caracteres pendientes. La división
en lectura, extracción y actualización permite que cada función tenga una
responsabilidad clara y facilita comprobar la gestión de memoria.

Las concatenaciones crean reservas nuevas porque `realloc` no está autorizado
por el subject. Después de copiar el contenido se libera siempre la reserva
anterior. Esta solución es directa y fácil de verificar, aunque concatenar
repetidamente una línea muy larga puede implicar copiar varias veces el
contenido acumulado.

## Recursos

- Subject oficial de `get_next_line`.
- Manual de `read`: `man 2 read`.
- Manual de `malloc`: `man 3 malloc`.
- Manual de `free`: `man 3 free`.
- Documentación sobre descriptores de archivo y variables estáticas en C.
- Conversaciones con compañeros para contrastar casos límite y gestión de
  memoria.

Se utilizó IA para revisar la claridad del algoritmo, detectar posibles casos
límite y comprobar la correspondencia entre reservas y liberaciones de
memoria. También se utilizó para mejorar la documentación. El código y su flujo
se revisaron posteriormente línea por línea para poder explicarlos y defender
las decisiones tomadas durante la evaluación.
