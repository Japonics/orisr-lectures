#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
#define CYCLE 1
pthread_mutex_t stick[N];
pthread_mutex_t eat;

void *diner(void *arg)
{
    int v;
    int eating = 0;
    v = *((int *)arg) + 1;
    while (eating < CYCLE)
    {
        printf("[%d]...hmm...co ja to miałem\n", v);
        sleep(v / 2);
        printf("[%d]...głodny\n", v);
        pthread_mutex_lock(&eat);
        pthread_mutex_lock((stick + v));
        pthread_mutex_lock((stick + (v + 1) % N));
        pthread_mutex_unlock(&eat);
        printf("[%d]...obiad...start\n", v);
        eating++;
        sleep(1);
        printf("[%d]...obiad...stop\n", v);
        pthread_mutex_unlock((stick + v));
        pthread_mutex_unlock((stick + (v + 1) % N));
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid[N];
    int n[N], i;
    pthread_mutex_init(&eat, NULL);
    for (i = 0; i < N; i++)
    {
        pthread_mutex_init((stick + i), NULL);
    }
    for (i = 0; i < N; i++)
    {
        *(n + i) = i;
        pthread_create((tid + i), NULL, diner, (void *)(n + i));
    }
    for (i = 0; i < N; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_exit(0);
}
