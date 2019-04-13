#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <cerrno>
#include <wait.h>

int main( void )
	{
	int status;
	switch( fork() )
	{
		case -1: //... kod na wypadek błędu dla PARENT
			printf( "<parent> oj niedobrze, niedobrze\n" );
			break;
		case 0: //...kod dla CHILD
			printf( "<child> pozdrowienia od potomka\n" );
			break;
		default: //...kod dla parent
			printf( "<parent> ja jestem PARENT\n" );
			wait( &status );
			printf("<parent> potomek skończył, zwrócił :%d\n",status);
	}
	return 0;
}