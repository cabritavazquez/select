# función select

Esta llamada duerme un proceso hasta que algún elemento de un conjunto de descriptores de E/S (ficheros regulares, pipes, sockets, ...) está preparado para:
 1.Hacer lecturas por él
 2.Hacer escrituras en él
 3.Notificar una situación excepcional sobre él

Para hacer funcionar nuestro programa, primero debemos crear las dos fifos:

> mkfifo <nombre_fifo1>
> mkfifo <nombre_fifo2>

Despues compilar y ejecutar nuestro programa select.c y por ultimo escribir en ambas fifos mediante la función cat:

> cat><nombre_fifo1>
> cat><nombre_fifo2>

Hasta que en ambas fifos no hagamos el cat nuestro programa no funcionará.
