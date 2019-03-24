#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

#define MASTER 0

int main(int argc, char *argv[])
{
    int world, current, len, n;
    char name[MPI_MAX_PROCESSOR_NAME + 1];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    MPI_Comm_rank(MPI_COMM_WORLD, &current);
    MPI_Get_processor_name(name, &n);
    if (current == MASTER)
    {
        printf("MASTER");
    }
    else
    {
        printf("SLAVE");
    }
    
    printf("\t%d.%d [%lu->%lu] | węzeł: %s\n", current + 1, world,
           (unsigned long)getppid(), (unsigned long)getpid(), name);
    MPI_Finalize();
    return 0;
}