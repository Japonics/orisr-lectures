#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
	int status;
	void bye(void);

	(void) atexit(bye);

	switch(fork())
	{
		case -1:
			printf("ERROR");
			break;
		case 0:
			exit(EXIT_SUCCESS);
			break;
		default:
			wait(&status);
			if (status) 
			{
				printf("RETURN ERROR");
				exit(EXIT_FAILURE);
			}
	}

	return EXIT_SUCCESS;
}

void bye(void)
{
	printf( "...i to wszystko w [%d]\n",(int)getpid());
	return;
}