//%cflags:-lpthread -lm

/** ejemplo de mutex en problema consumidor productor
** 	compilar con threads: gcc mutex-test.c -o mutex-test -lpthread
*/

#include <stdio.h>
#include <termios.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER 16
#define MAX_DATOS 32

pthread_mutex_t mutex;
pthread_cond_t vacio, lleno;
int buffer[MAX_BUFFER], num_datos;

// proceso consumidor
void *consumidor()
{
    struct datos_tipo_cond_mutex *datos_proceso;
    int a, i, j, p, posicion = 0, dato;

    for (i = 0; i < MAX_DATOS; i++)
    {
        pthread_mutex_lock(&mutex);
        while (num_datos == 0)
            pthread_cond_wait(&vacio, &mutex);

        dato = buffer[posicion];
        if (posicion == 15)
            posicion = 0;
        else
            posicion++;

        num_datos--;

        if (num_datos == MAX_BUFFER - 1)
            pthread_cond_signal(&lleno);

        pthread_mutex_unlock(&mutex);
        printf("\nse ha consumido el dato: %d", dato);
        fflush(stdout);
        sleep(1);
    }
    pthread_exit(0);

    //
}

//proceso productor
void *productor()
{
    struct datos_tipo_cond_mutex *datos_proceso;
    int a, i, j, p, posicion = 0, dato;

    for (i = 0; i < MAX_DATOS; i++)
    {
        pthread_mutex_lock(&mutex);
        while (num_datos == MAX_BUFFER)
            pthread_cond_wait(&lleno, &mutex);

        buffer[posicion] = i;
        dato = i;

        if (posicion == 15)
            posicion = 0;
        else
            posicion++;
        num_datos++;
        if (num_datos == 1)
            pthread_cond_signal(&vacio);

        pthread_mutex_unlock(&mutex);
        printf("\nse ha producido el dato: %d", dato);
        fflush(stdout);
        //	 	sleep(1);
    }
    pthread_exit(0);
    //
}

int initCondMutex()
{
    int error;
    char *valor_devuelto;

    /* Variables para hilos*/
    pthread_t idhilo1, idhilo2, idhilo3, idhilo4;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&lleno, NULL);
    pthread_cond_init(&vacio, NULL);

    error = pthread_create(&idhilo1, NULL, (void *)productor, NULL);
    if (error != 0)
    {
        perror("No puedo crear hilo");
        exit(-1);
    }

    error = pthread_create(&idhilo2, NULL, (void *)consumidor, NULL);
    if (error != 0)
    {
        perror("No puedo crear thread");
        exit(-1);
    }

    pthread_join(idhilo2, (void **)&valor_devuelto);
    pthread_join(idhilo1, (void **)&valor_devuelto);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&lleno);
    pthread_cond_destroy(&vacio);
    return 0;
}
