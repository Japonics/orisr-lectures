#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int N = 0;

void *thread(void *arg)
{
    int n, i;
    for (i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex);
        n = N;
        n++;
        printf("thread() [%lu] \n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
        N = n;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid;
    int i;

    if (pthread_create(&tid, NULL, thread, NULL))
    {
        perror("...pthread_create()...");
        exit(1);
    }

    for (i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex);
        N--;
        printf("main() [%lu] \n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }

    if (pthread_join(tid, NULL))
    {
        perror("...pthread_join()...");
        exit(2);
    }

    if (pthread_mutex_destroy(&mutex))
    {
        perror("...pthread_mutex_destroy()...");
        exit(2);
    }

    printf("\n gloalnie N = %d, po wykonaniu 5 + 5 iteracji \n", N);
    return 0;
}
