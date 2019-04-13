#include<unistd.h>
#include<stdio.h>

int main( void )
{
	char *arg[4];
	arg[0]="pierwszy"; arg[1]="drugi"; arg[2]="trzeci"; arg[3]='\0';
	printf( "- wywołanie (samobójcze) potomka ----------\n" );
	execv( "./p3",arg );
	return 0;
}