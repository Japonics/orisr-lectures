#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ENDLESS 1

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long int buffer;
int n,no;

unsigned long int produce( void )
{
    return (42*n*n*n + 270*n*n - 26436*n + 250703);
}

void append( unsigned long int v )
{
    buffer = v; return;
}

unsigned long int take( void )
{
    return buffer;
}

void* producer( void *arg )
{
    unsigned long int v;
    printf( "[%lu] producer, start\n",(unsigned long)pthread_self() );
    while( ENDLESS )
    {
        pthread_mutex_lock(&mutex);
        v = produce();
        append( v );
        pthread_mutex_unlock(&mutex);
    }

    printf( "[%lu] producer, stop\n",(unsigned long)pthread_self() );
    pthread_exit(NULL);
}

void *consumer( void* arg )
{
    unsigned long int v;
    printf( "[%lu] consumer, start\n",(unsigned long)pthread_self() );

    for( n=0;n<no;n++ )
    {
        pthread_mutex_lock( &mutex );
        v = take();
        pthread_mutex_unlock( &mutex );
        printf("%d -> %lu\n",n,v );
    }

    printf( "[%lu] consumer, stop\n",(unsigned long)pthread_self() );
    pthread_exit(NULL);
}

int main( int argc,char** argv )
{
    pthread_t _pid;
    pthread_t _cid;

    if(argc > 1)
    {
        sscanf(argv[1],"%d", &no); 
        
        if(no > 40)
        {
            no = 40;
        }

        pthread_create( &_cid,NULL,consumer,NULL );
        pthread_create( &_pid,NULL,producer,NULL );
        pthread_join( _cid,NULL ); //...łączone tylko wątki konsumenta (-ów)
    }
    else {
         printf( "...%s no= ???\n",argv[0] ); 
    }

    return 0;
}