*Este proyecto ha sido creado como parte del currículo de 42 por andrcarr.*

# get\_next\_line

## Descripción

`get\\\_next\\\_line` implementa una función en C que devuelve una línea cada vez
desde un descriptor de archivo. La línea devuelta incluye el carácter de salto
de línea (`\\\\n`) cuando está presente. Cuando no quedan más datos por leer o se
produce un error, la función devuelve `NULL`.

El objetivo principal del proyecto es aprender a trabajar con descriptores de
archivo, la función `read`, variables estáticas y memoria dinámica.



Prototipo de la función:

```c
char \\\*get\\\_next\\\_line(int fd);
```

## Instrucciones

Los archivos que forman la parte obligatoria son:

* `get\\\_next\\\_line.c`
* `get\\\_next\\\_line\\\_utils.c`
* `get\\\_next\\\_line.h`
* 

Para compilar el proyecto

(junto con un archivo de prueba `main.c`):

```sh
cc -Wall -Wextra -Werror -D BUFFER\\\_SIZE=42 \\\\
get\\\_next\\\_line.c get\\\_next\\\_line\\\_utils.c main.c -o gnl
```

El valor de `BUFFER\\\_SIZE` puede modificarse durante la compilación:

```sh
cc -Wall -Wextra -Werror -D BUFFER\\\_SIZE=1 \\\\
get\\\_next\\\_line.c get\\\_next\\\_line\\\_utils.c main.c -o gnl
```

Para ejecutar el programa de prueba:

```sh
./gnl
```

El ejemplo busca un archivo llamado `archivo.txt` en el directorio actual.

El archivo `main.c` se utiliza únicamente para realizar pruebas y no forma
parte de la entrega.

### Ejemplo de `main.c` para pruebas

El siguiente programa abre un único archivo y llama repetidamente a
`get\\\_next\\\_line` hasta que la función devuelve `NULL`:



```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		number;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	number = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Línea %d: [%s]", number, line);
		free(line);
		number++;
		line = get_next_line(fd);
	}
	printf("get_next_line devuelve NULL\n");
	if (fd > 2)
		close(fd);
	return (0);
}

```

Este `main` utiliza `open`, `printf` y `close` únicamente para probar la
función. Estas llamadas no forman parte de la implementación entregable de
`get\\\_next\\\_line`.



## Algoritmo y decisiones técnicas

El algoritmo utiliza una variable estática llamada `stash` para conservar entre
llamadas los caracteres que se han leído, pero que todavía no se han devuelto
como parte de una línea.

### Flujo de ejecución

1. Se comprueban el descriptor `fd`, el valor de `BUFFER\\\_SIZE` y la legibilidad
del descriptor mediante `read(fd, NULL, 0)`.
2. Si `stash` ya contiene un salto de línea, no se realiza una nueva lectura.
3. En caso contrario, `ft\\\_read\\\_and\\\_save` lee bloques de hasta `BUFFER\\\_SIZE`
bytes y los añade a `stash`.
4. La lectura termina cuando se encuentra `\\\\n`, se alcanza el final del archivo
o se produce un error.
5. `ft\\\_extract\\\_line` crea una nueva cadena desde el principio de `stash` hasta
el primer `\\\\n` incluido. Si no existe `\\\\n`, copia hasta el final.
6. `ft\\\_clean\\\_stash` elimina la línea que se va a devolver y conserva los
caracteres posteriores para la siguiente llamada.
7. Se liberan las reservas que dejan de ser necesarias y se devuelve la línea.

### Decisiones técnicas

\* Se utiliza `read(fd, NULL, 0)` para comprobar el descriptor sin consumir
datos del archivo.
\* `stash` es estático porque debe conservar su valor después de finalizar una
llamada a `get\\\_next\\\_line`.
\* `ft\\\_append\\\_buffer` concatena el contenido acumulado con el nuevo bloque y
libera el `stash` anterior.
\* `ft\\\_extract\\\_line` devuelve una reserva independiente para que el programa que
llama a `get\\\_next\\\_line` pueda liberarla.
\* `ft\\\_clean\\\_stash` conserva únicamente el contenido posterior a la línea
devuelta y libera el estado anterior.
\* La lectura se detiene en cuanto existe una línea completa, evitando leer todo
el archivo por adelantado.
\* Las funciones auxiliares se separan según su responsabilidad para facilitar
la lectura del código y el control de la memoria.

## 

## Recursos

\* Subject oficial de `get\\\_next\\\_line`.
\* Manual de `read`
\* Manual de `malloc`
\* Manual de `free`
\* Documentación sobre descriptores de archivo y variables estáticas en C.
\* Conversaciones con compañeros para contrastar casos límite y gestión de
memoria.

Se utilizó IA para detectar posibles casos límite y mejorar la documentación.


