#include<stdio.h>
#include<unistd.h>

int main( void )
{
	printf("Current ID\t%d\n",(int)getpid() );
	printf("Parent ID\t%d\n",(int)getppid());
	return 0;
}
