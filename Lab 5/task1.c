#include <stdio.h>
#include <mpi.h>

int main( int argc,char **argv )
{
    MPI_Init( &argc,&argv );
    printf( "...programowanie z MPI jest proste\n" );
    MPI_Finalize();
    return 0;
}