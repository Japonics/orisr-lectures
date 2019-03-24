#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int N = 0;

void *thread(void *arg)
{
    int n, i;
    for (i = 0; i < 5; i++)
    {
        n = N;
        n++;
        printf("thread() [%lu] \n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
        N = n;
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
        N--;
        printf("main() [%lu] \n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
    }

    if (pthread_join(tid, NULL))
    {
        perror("...pthread_join()...");
        exit(2);
    }

    printf("\n gloalnie N = %d, po wykonaniu 5 + 5 iteracji \n", N);
    return 0;
}
