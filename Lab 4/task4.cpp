#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
unsigned long int n = 0;
const unsigned long int no = 10;

void *watch(void *arg)
{
    printf("[%lu] watch(): start\n", (unsigned long)pthread_self());
    pthread_mutex_lock(&mutex);
    while (n < no)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("[%lu] watch(): V() %lu\n", (unsigned long)pthread_self(), n);
    pthread_mutex_unlock(&mutex);
    printf("[%lu] watch(): stop\n", (unsigned long)pthread_self());
    
}

void *worker(void *arg)
{
    for (n = 0; n < 25; n++)
    {
        //pthread_mutex_lock(&mutex);
        printf("[%lu] worker(): V() %lu\n", (unsigned long)pthread_self(), n);
        if (!(n - no)) 
        {
            pthread_cond_broadcast(&cond);
            break;
        }
        //pthread_mutex_lock(&mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t tid[2];

    pthread_mutex_init(&mutex, NULL);
    pthread_create((tid + 0), NULL, worker, NULL);
    pthread_create((tid + 1), NULL, watch, NULL);
    pthread_join(*(tid + 1), NULL);
    pthread_join(*(tid + 0), NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("[%lu] main(): stop\n", (unsigned long)pthread_self());

    return 0;
}