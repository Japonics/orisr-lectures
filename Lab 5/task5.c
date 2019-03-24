#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MASTER 0
#define TAG 'K' + 'M'
#define MEGA 100000LU

int main(int argc, char *argv[])
{
    unsigned long N, counter;
    double x, Sxx, Var;
    int world, current, len;
    char name[MPI_MAX_PROCESSOR_NAME + 1];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    if (argc > 1)
    {
        sscanf(argv[1], "%lu", &N);
    }
    else
    {
        N = 0;
    }
    N = (N < 1) ? (1 * MEGA) : (N * MEGA);
    MPI_Comm_rank(MPI_COMM_WORLD, &current);
    MPI_Get_processor_name(name, &len);
    printf("(proces%2d)@%s", current, name);
    if (current == MASTER)
    {
        printf("...ilość składników %lu*%lu\n", N / MEGA, MEGA);
        for (current = MASTER + 1, Sxx = 0.0; current < world; current++)
        {
            MPI_Recv((void *)&x, 1, MPI_DOUBLE, current, TAG, MPI_COMM_WORLD, &status);
            Sxx += x;
        }
        Var = Sxx / (N - 1);
        printf("...MASTER zyskał wariancję Var=%g\n", Var);
        printf(" dla %lu*%lu składników sumy\n", N / MEGA, MEGA);
    }
    else
    {
        for (counter = current, Sxx = 0.0; counter <= N; counter += (world - 1))
        {
            x = (double)rand() / RAND_MAX;
            Sxx += (x - 0.5) * (x - 0.5);
        }
        printf("...SLAVE wysyła sumę %g\n", Sxx);
        MPI_Send((void *)&Sxx, 1, MPI_DOUBLE, MASTER, TAG, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}