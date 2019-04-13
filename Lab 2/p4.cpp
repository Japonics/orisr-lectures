#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd[2];
	int pid, status;

	FILE* stream;

	if (pipe(fd) < 0) 
	{
		printf("...blad otwarcia lacza\n");
		exit(1);
	}

	switch(fork())
	{
		case -1:
			perror("<!> blad inicjalizacji potomka");
			exit(1);
			break;
		case 0:
			printf("<!>\t potomek [%d] startuje \n", (int)getpid());
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			printf("-----------------------------------------\n");
			execl("/usr/bin/sort", "sort", "--reverse", (char*) NULL);
		default:
			close(fd[0]);
			stream = fdopen(fd[1], "w");
			fprintf(stream, "\tAaaaa\n");
			fprintf(stream, "\tBbbbb\n");
			fprintf(stream, "\tCccc\n");
			fprintf(stream, "\tDdddd\n");
			fflush(stream);
			close(fd[1]);
			wait(&status);
			printf("-----------------------------------------\n");
			printf("<!> \t potomek [%d] zakonczyl dzialanie i zwrocil [%d] \n", (int)getpid(), status);
	}

	return 0;
}