#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int N = 0;

void *thread(void *param)
{
    pthread_mutex_lock(&mutex);
    {
        int id = (intptr_t) param;
        N += id;
    }

    pthread_mutex_unlock(&mutex);
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


        if (!(tid = (pthread_t*)calloc((size_t)n, sizeof(pthread_t))))
        {
            perror("...calloc()...");
            exit(2);
        }

        for (i = 0; i < n; i++)
        {
            if (pthread_create((tid + i), NULL, (void*(*)(void*))thread, (void*)(intptr_t)(i + 1)))
            {
                free((void*) tid);
                perror("...pthread_create()...");
                exit(2);
            }
        }

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

        if (pthread_mutex_destroy(&mutex))
        {
            perror("...pthread_mutex_destroy()...");
            exit(2);
        }

        printf("|\n| %s%d%s%d\n|\n", "suma ciagu n =", n, "liczb naturalnych wynosi n * (n + 1) / 2 =", N);
    }
    else
    {
        printf("...wywolanie programu %s <ilosc watkow>\n", argv[0]);
        exit(1);
    }

    return 0;
}