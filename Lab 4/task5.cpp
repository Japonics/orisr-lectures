#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_barrier_t barrier;
unsigned count;

void *thread(void *arg)
{
    printf("[%li] thread wait signal ...!\n", (unsigned long)pthread_self());
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t* tid;
    int i, n;

    if (argc > 1)
    {
        sscanf(argv[1], "%d", &n);
        if (n < 2) 
        {
            printf("... n < 2, przyjeto n = 2... \n");
            n = 2;
        }

        count = n + 1;
        if (!(tid = (pthread_t*)calloc((size_t) n, sizeof(pthread_t))))
        {
            perror("...calloc()...");
        }

        pthread_barrier_init(&barrier, NULL, count);

        for (i = 0; i < n; i++)
        {
            if (pthread_create((tid + i), NULL, thread, NULL))
            {
                free((void*) tid);
                perror("...pthread_create()...");
                exit(2);
            }
        }
        
        printf("[%lu] main()...?\n", (unsigned long) pthread_self());
        sleep(1);
        pthread_barrier_wait(&barrier);
        printf("[%lu] main()... done?\n", (unsigned long) pthread_self());

        for (i = 0; i < n; i++)
        {
            if (pthread_join(*(tid + i), NULL))
            {
                free((void*)tid);
                perror("...pthread_join()...");
                exit(2);
            }
        }

        free((void*)tid);
        if (pthread_barrier_destroy(&barrier))
        {
            perror("...pthread_barrier_destroy()...");
            exit(2);
        }
    }
    else 
    {
        printf("...wywolanie programu %s <ilosc watkow> \n", argv[0]);
        exit(1);
    }

    return 0;
}