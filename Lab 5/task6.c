#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MASTER 0
#define MEGA 100000LLU

int main(int argc, char *argv[])
{
    unsigned long long N, i;
    double x, Sxx, Var;
    int world, current;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    if (argc > 1)
    {
        sscanf(argv[1], "%llu", &N);
    }
    else
    {
        N = 0;
    }
    N = (N < 1) ? (1 * MEGA) : (N * MEGA);
    MPI_Comm_rank(MPI_COMM_WORLD, &current);
    for (i = current, Sxx = 0.0; i < N; i += world)
    {
        x = (double)rand() / RAND_MAX;
        Sxx += (x - 0.5) * (x - 0.5);
    }
    MPI_Reduce(&Sxx, &Var, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if (current == MASTER)
    {
        printf("Ilość elementów N*M=%llu*%llu\n", N / MEGA, MEGA);
        printf("Otrzymana wartość Var= %lf\n", Var / (N - 1));
    }
    MPI_Finalize();
    return 0;
}