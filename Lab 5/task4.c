#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MASTER 0
#define TAG 'R' + 'i' + 'R'

int main(int argc, char *argv[])
{
    int current, world, counter;
    double x, Sx;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    MPI_Comm_rank(MPI_COMM_WORLD, &current);
    srand((unsigned)time(NULL));
    if (current != MASTER)
    {
        x = (double)rand() / RAND_MAX;
        MPI_Send((void *)(&x), 1, MPI_DOUBLE, MASTER, TAG, MPI_COMM_WORLD);
    }
    else
    {
        for (counter = MASTER + 1, Sx = 0.0; counter < world; counter++)
        {
            MPI_Recv((void *)(&x), 1, MPI_DOUBLE, counter, TAG, MPI_COMM_WORLD, &status);
            Sx += x;
        }

        printf( "\nProces %d odebrał od %d do %d, sumę Sx=%f\n\n",MASTER,MASTER+1,world-1,Sx );
    }

    MPI_Finalize();
    return 0;
}