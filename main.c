#include <stdbool.h>
#include "tuberias/tuberia.c"
#include "mutex/mutex.c"
#include "mutex/mutexCondicional.c"
#include "semaforos/semaforo.c"

/**
 * The function clear_stream is used to clear the pointer when scanf function is used
 * @param in is a pointer to a document
*/
void clear_stream(FILE *in)
{
    int ch;
    
    clearerr(in);
    
    do
        ch = getc(in);
    while (ch != '\n' && ch != EOF);
    
    clearerr(in);
}

int main(int argc, char const *argv[])
{
    bool exitValue = false;
    int selection;
    char finish;

    printf("=====================\n");
    printf("Bienvenido al Sistema\n");
    printf("=====================\n");

    while (!exitValue){
        printf("Que desea hacer?\n");
        printf("1) Ejecutar código de las pipes\n");
        printf("2) Ejecutar código de los semaforos\n");
        printf("3) Ejecutar código del mutex\n");
        printf("4) Ejecutar código del mutex condicional\n");

        scanf("%d", &selection);
        clear_stream(stdin);
        system("clear");

        switch (selection){
            case 1:
                initPipe();
            break;

            case 2:
                initSem();
            break;

            case 3:
                initMutex();
            break;

            case 4:
                initCondMutex();
            break;

            default:
                printf("No se reconocio su selección, intenete nuevamante");
            break;
        }

        // Finalizar programa
        printf("\nPrograma finalizado, desea volver a ejecutar? (y/n)\n");
        fflush(stdout);
        scanf("%c", &finish);
        if (finish == 'n') exitValue = true;
    }
    
    return 0;
}
