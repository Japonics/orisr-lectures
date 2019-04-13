#include<unistd.h>
#include<stdio.h>

int main( void )
{
	char *arg1="pierwszy", *arg2="drugi",*arg3="trzeci";
	printf( "- wywołanie (samobójcze) potomka ----------\n" );
	execl( "./p2",arg1,arg2,arg3,'\0' );
	return 0;
}