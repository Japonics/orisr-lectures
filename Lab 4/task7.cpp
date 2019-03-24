#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define R 4
#define W 2
#define N 5

#define ENDLESS 1

pthread_mutex_t wmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;

int counter;

void* writer( void* arg )
{
    int n;
    for(n = 0; n < N; n++)
    {
        pthread_mutex_lock( &wmutex );
        printf("[%lu] pisarz, start\n",(unsigned long)pthread_self());
        sleep(1); //...wykonanie operacji przez pisarza (tu: pusta)
        printf("[%lu] pisarz, stop\n",(unsigned long)pthread_self() );
        pthread_mutex_unlock( &wmutex );
        sleep(n % 2); //...aby nieco utrudnić koordynację
    }
    
    pthread_exit( NULL );
}

void* reader( void* arg )
{
    int n = 0;

    while(ENDLESS)
    {
        pthread_mutex_lock( &rmutex );
        counter++;

        if(counter == 1)
        {
            pthread_mutex_lock(&wmutex);
        }

        pthread_mutex_unlock( &rmutex );
        printf( "[%lu] czytelnik, start\n",(unsigned long)pthread_self() );
        sleep(1);
        printf( "[%lu] czytelnik, stop\n",(unsigned long)pthread_self() );
        pthread_mutex_lock( &rmutex );
        counter--;

        if( !counter )
        { 
            pthread_mutex_unlock(&wmutex);
        }

        pthread_mutex_unlock(&rmutex);
        sleep(n % 3);
        n++;
    }

    pthread_exit(NULL);
}

int main( void )
{
    pthread_t rid[R];
    pthread_t wid[W];
    int t;
    counter = 0;
    for(t = 0; t < R; t++)
    {
        pthread_create((rid+t), NULL, reader, NULL);
    }

    for(t = 0; t < W; t++)
    {
        pthread_create((wid+t), NULL, writer, NULL);
    }
    
    for(t = 0; t < W; t++)
    {
        pthread_join(*(wid+t), NULL);
    }

    return 0;
}