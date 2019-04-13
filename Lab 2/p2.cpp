#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

int main(void)
{
	int fd[2], n;
	char line[PIPE_BUF];

	if (pipe(fd) < 0) 
	{
		printf("... blad otwarcia lacza");
		exit(1);
	}

	switch(fork())
	{
		case -1:
			perror("<!> blad inicjalizacji potomka");
			exit(1);
			break;
		case 0:
			close(fd[0]);
			write(fd[1], "\n\t[pozdrowienia od potomka]\n\n", 29);
			close(fd[1]);
			exit(0);
		default:
			close(fd[1]);
			n = read(fd[0], (void*)line, PIPE_BUF);
			close(fd[0]);
			write(STDOUT_FILENO, line, n);
	}

	return 0;
}