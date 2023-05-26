# MINISHELL

## Programacion de una shell en un entorno de linux hecho en C

## Tabla de contenido
* [Funciones](#Funciones)
    * [fork](#fork)

### Funciones

> fork

la funcion `fork()` en C se utiliza para crear un nuevo proceso duplicando el proceso 
existente. 
El proceso original se llama **padre** y el nuevo proceso se llama **hijo**.

le sintaxis basica es:
```c
#include <sys/type.h>
#include <unistd.h>

pid_t   fork(void);
```
El return:

- Valor negativo: el llamado a `fork()` ha fallado y no se ha podido crear un nuevo proceso
- Igual a 0: el proceso actual es el **hijo**
- Mayor que 0: el proceso actual es el **padre** y el valor retornado es el ID del proceso 
hijo

Ejemplo de `fork()`:
```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        fprintf(stderr, "Error al crear el proceso hijo\n");
        return 1;
    } else if (pid == 0) {
        // Código ejecutado por el proceso hijo
        printf("Proceso hijo: ID = %d\n", getpid());
    } else {
        // Código ejecutado por el proceso padre
        printf("Proceso padre: ID = %d, ID del proceso hijo = %d\n", getpid(), pid);
    }

    return 0;
}
```
El proceso padre crea un nuevo proceso hijo llamado a `fork()`.
El proceso hijo imprime su ID y el proceso padre imprime su proprio ID y el ID del proceso hijo
Ambos procesos continuan ejecutando el codigo despues de la llamada a `fork()`, pero cada uno tiene su propria
copia de las variables y el contexto de la funcion.
