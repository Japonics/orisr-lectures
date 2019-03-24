#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int go = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg)
{
    printf("[%lu] producent: ??? \n", (unsigned long) pthread_self());
    sleep(1);

    pthread_mutex_lock(&mutex);
    go = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    printf("[%lu] konsument: czeka... \n", (unsigned long)pthread_self());

    pthread_mutex_lock(&mutex);
    while (!go)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);
    printf("[%lu] konsument: kontynuacja \n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t cid, pid;

    if (pthread_create(&cid, NULL, consumer, NULL))
    {
        perror("...pthread_create()... consumer");
        exit(1);
    }

    if (pthread_create(&pid, NULL, producer, NULL))
    {
        perror("...pthread_create()... producer");
        exit(1);
    }

    if (pthread_join(cid, NULL)) 
    {
        perror("...pthread_join()...");
        exit(1);
    }

    if (pthread_join(pid, NULL)) 
    {
        perror("...pthread_join()...");
        exit(1);
    }

    return 0;
}