#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

int main()
{
	int one[2], two[2];
	int pid, status;
	double x = 1.0, y = 1.0;

	printf("\t [%d] nadrzedny, start \n\n", (int)getpid());

	if (pipe(one) < 0 || pipe(two) < 0) 
	{
		printf("...blad otwarcia lacza\n");
		exit(1);
	}

	switch(pid = (int)fork())
	{
		case -1:
			perror("<!> blad inicjalizacji potomka");
			exit(1);
			break;
		case 0:
			printf("<!>\t potomek [%d] startuje \n", (int)getpid());
			close(one[1]);
			close(two[0]);
			read(one[0], (void*) &x, sizeof(double));
			printf("\t[%d] otrzymal x = %f \n", (int)getpid(), x);
			x = x * M_PI;
			printf("\t [%d] wykonal f(x) = y, wysyla y = %f \n", (int)getpid(), x);
			write(two[1], (void*) &y, sizeof(double));
			printf("\t [%d] potomek stop \n\n", (int)getpid());
			exit(0);
		default:
			close(one[0]);
			close(two[1]);
			printf("\t [%d] wysyla do potomka [%d] x = %f \n\n", (int)getpid(), pid, x);
			write(one[1], (void*) &x, sizeof(double));
			read(two[0], (void*) &y, sizeof(double));
			wait(&status);
			printf("\t [%d] potomek, zwrocil sterowanie, kod powrotu [%d] \n", pid, status);
			printf("\t [%d] otrzymal y = %f \n", (int)getpid(), y);
			printf("\t [%d] nadrzedny, stop \n", (int)getpid());
	}

	return 0;
}