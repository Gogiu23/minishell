# MINISHELL

## Programacion de una shell en un entorno de linux hecho en C

## Tabla de contenido
* [Funciones](#Funciones)
    * [fork()](#fork)
    * [pipe](#pipe)
    * [execve](#execve)
    * [access](#access)
    * [perror](#perror)

## Funciones

### fork( )

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

### pipe( )

La funcion `pipe()` se utiliza para crear descriptores de archivo
interconectados. 

Se declara de la siguiente forma
```c
#include <unistd.h>

int pipe(int pipefd[2]);
```
***pipefd*** es un arreglo de enteros que contendrá los descriptores
de archivo para la lectura (`pipefd[0]`) y la escritura (`pipefd[1]`).

***Ejemplo***
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char buffer[100];
    pid_t pid;

    // Crear el pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Crear un proceso hijo
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Código del proceso hijo
        close(pipefd[1]);  // Cerrar el extremo de escritura del pipe en el proceso hijo
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Proceso hijo: %s\n", buffer);
        close(pipefd[0]);  // Cerrar el extremo de lectura del pipe en el proceso hijo
    } else {
        // Código del proceso padre
        close(pipefd[0]);  // Cerrar el extremo de lectura del pipe en el proceso padre
        printf("Proceso padre: Escribiendo en el pipe\n");
        write(pipefd[1], "Hola, hijo!", 12);
        close(pipefd[1]);  // Cerrar el extremo de escritura del pipe en el proceso padre
    }

    return 0;
}
```
En este ejemplo, se crea un pipe con pipe(). Luego, se crea un proceso hijo utilizando fork(). El proceso padre escribe la cadena "Hola, hijo!" en el extremo de escritura del pipe usando write(). El proceso hijo lee la cadena del extremo de lectura del pipe usando read(). Luego, ambos procesos cierran los descriptores de archivo no utilizados.

### execve( )

La funcion `execve()` se utiliza para ejecutar un programa externo desde otro programa.
Se crea una imagen nueva que remplaza la actual del programa que se esta ejecutando.

```c
int execve(const char *pathname, char *const argv[], char *const envp[])
```
> Parametros
- `pathname`: Es una cadena que especifica donde se encuentra el binario del programa que se va a 
ejecutar
- `argv`: Es el arreglo de cadenas de caracteres que representa los argumentos pasados al programa.
El primer elemento del arreglo (`argv[0]`) suele ser el nombre del programa.
- `envp`: Es un arreglo de cadenas de caracteres que representa el entorno donde se ejecutará 
el nuevo programa. El entorno consiste en variables de entorno como `PATH` etc.
El ultimo elemento del arreglo debe ser un puntero nulo (`NULL`).

***Ejemplo***
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = { "ls", "-l", NULL };
    char *env[] = { NULL };

    if (execve("/bin/ls", args, env) == -1) {
        perror("execve");
        return 1;
    }

    printf("Esta línea no se imprimirá si execve tiene éxito.\n");

    return 0;
}
```
> Valores de retorno

`execve` si tiene exito no devuelve un valor. Si devuelve `-1` si ha habido un error y asigna la 
variable `errno` con el codigo de error correspondiente:

```bash
[E2BIG]         The number of bytes in the new process argument list is larger than the system-
                imposed limit.  This limit is specified by the sysctl(3) MIB variable KERN_ARGMAX.

[EACCES]        Search permission is denied for a component of the path prefix.

[EACCES]        The new process file is not an ordinary file.

[EACCES]        The new process file mode denies execute permission.

[EACCES]        The new process file is on a filesystem mounted with execution disabled (MNT_NOEXEC
                in ⟨sys/mount.h⟩).

[EFAULT]        The new process file is not as long as indicated by the size values in its header.

[EFAULT]        Path, argv, or envp point to an illegal address.

[EIO]           An I/O error occurred while reading from the file system.

[ELOOP]         Too many symbolic links were encountered in translating the pathname.  This is taken
                to be indicative of a looping symbolic link.

[ENAMETOOLONG]  A component of a pathname exceeded {NAME_MAX} characters, or an entire path name
                exceeded {PATH_MAX} characters.

[ENOENT]        The new process file does not exist.

[ENOEXEC]       The new process file has the appropriate access permission, but has an unrecognized
                format (e.g., an invalid magic number in its header).

[ENOMEM]        The new process requires more virtual memory than is allowed by the imposed maximum
                (getrlimit(2)).

[ENOTDIR]       A component of the path prefix is not a directory.

[ETXTBSY]       The new process file is a pure procedure (shared text) file that is currently open
                        for writing or reading by some process.
```

### access( )

La función `access()` en C se utiliza para verificar si un archivo o directorio tiene ciertos permisos específicos. 
Permite determinar si el usuario actual tiene permisos para leer, escribir o ejecutar un archivo o directorio.

Aquí está su firma:

```c
int access(const char *path, int mode);
```

La función `access()` toma dos argumentos: `path` y `mode`. `path` es una cadena que representa la ruta al archivo o directorio que se desea verificar, y 
`mode` especifica los permisos que se desean verificar. Puede ser una combinación de las siguientes constantes definidas en la biblioteca `unistd.h`:

- `R_OK`: Comprueba si el archivo o directorio es legible.
- `W_OK`: Comprueba si el archivo o directorio es escribible.
- `X_OK`: Comprueba si el archivo o directorio es ejecutable.
- `F_OK`: Comprueba si el archivo o directorio existe.

La función `access()` devuelve 0 si los permisos especificados están disponibles para el archivo o directorio, 
y devuelve -1 si no están disponibles o si se produce algún error. 
En caso de error, se puede utilizar la función `errno` para determinar el motivo específico del error.

Aquí hay un ejemplo de cómo usar la función `access()` para verificar si un archivo es legible y escribible:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "archivo.txt";

    if (access(filename, R_OK | W_OK) == 0) {
        printf("El archivo es legible y escribible.\n");
    } else {
        perror("No se pueden acceder al archivo");
        return 1;
    }

    return 0;
}
```

En este ejemplo, se verifica si el archivo "archivo.txt" es legible y escribible utilizando la función `access()` con los permisos `R_OK` y `W_OK`. 
Si los permisos están disponibles, se muestra un mensaje indicando que el archivo es legible y escribible. 
De lo contrario, se imprime un mensaje de error utilizando `perror()`.

### perror( )

La funcion `perror( )` desribe un mensaje de error por la salida estandard. Recibe como argumento una cadena de caracteres que se
utilizara como prefijo en el mensaje de error.

La funcion `perror()` se encuentra en la biblioteca de C `stdio.h`. Su declaracion es la siguiente:
```c
void    perror(const char *str);
```

Obtiene la descripcion de error de la variable `errno`, la cual es una variable global definida en `errno.h`.
Dicha variable almacena el numero del ultimo error encontrado en el programa. `perror()` toma ese numero de error y busca 
una cadena descriptiva correspondiente en una tabla interna.

Por lo tanto, el mensaje impreso es una concatenacion de la cadena `str` seguida de la descripcion del error obtenida a partir
de `errno`.

***Ejemplo***
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    FILE *file = fopen("archivo_inexistente.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Resto del código...

    return 0;
}
```

> Si quieremos ver el valor de ***errno*** podemos escribir en bash `echo $?` y tendremos el valor actual de la variable 
`ERRNO`.
