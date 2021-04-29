//%cflags:-lpthread -lm

/** 	compilar con math.h   -lm
** 	compilar con threads: -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PROCESOS 1
/* Variables para semaforos*/
pid_t pipeId;
int pipes[2];

struct datos_tipo_pipe
{
    int dato;
    int p;
}

* procesoPipe(void *datos)
{
    struct datos_tipo_pipe
 *datos_proceso;
    datos_proceso = (struct datos_tipo_pipe
 *)datos;
    int a, i, j, p, value;

    read(pipes[0], &value, sizeof(int));

    a = datos_proceso->dato;
    p = datos_proceso->p;
    for (i = 0; i <= p; i++)
    {
        printf("%i ", a);
    }

    fflush(stdout);
    sleep(2);
    for (i = 0; i <= p; i++)
    {
        printf("- ");
    }
    fflush(stdout);
    write(pipes[1], &value, sizeof(int));
}

int initPipe()
{
    int error, value = 1;
    char *valor_devuelto;
    /* Variables para hilos*/
    struct datos_tipo_pipe
 hilo1_datos, hilo2_datos;
    pthread_t idhilo1, idhilo2, idhilo3, idhilo4;

    hilo1_datos.dato = 1;
    hilo2_datos.dato = 2;
    hilo1_datos.p = 10;
    hilo2_datos.p = 5;

    pipeId = pipe(pipes);

    if (pipeId != 0)
    {
        perror("No puedo crear la pipe");
        exit(-1);
    }

    write(pipes[1], &value, sizeof(int));

    error = pthread_create(&idhilo1, NULL, (void *)procesoPipe, (void *)(&hilo1_datos));
    if (error != 0)
    {
        perror("No puedo crear hilo");
        exit(-1);
    }

    error = pthread_create(&idhilo2, NULL, (void *)procesoPipe, (void *)(&hilo2_datos));
    if (error != 0)
    {
        perror("No puedo crear thread");
        exit(-1);
    }
    pthread_join(idhilo2, (void **)&valor_devuelto);
    pthread_join(idhilo1, (void **)&valor_devuelto);

    close(pipes[0]);
    close(pipes[1]);
    
    return 0;
}
