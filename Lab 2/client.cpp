#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

int main (void)
{

	int fd, run;
	pid_t pid;
	char cmd;
	char buffer[256];


	pid = getpid();
	printf("\n[%d] *K*L*I*E*N*T* [%d]\n\n", pid, pid);

	if ((fd = open("pipe", O_WRONLY)) > 0) 
	{
		run = 1;
	}
	else 
	{
		printf("!.!.. nie znaleziono lacza ..!.\n\n");
		run = 0;
	}

	while (run)
	{
		printf("\t? ... \t");
		fgets(buffer, 256, stdin);
		sscanf(buffer, "%c", &cmd);
		cmd = toupper(cmd);
		write(fd, &pid, sizeof(pid_t));
		write(fd, &cmd, sizeof(char));

		if (cmd == 'Q')
		{
			run = 0;
			close(fd);
		}
	}	

	return 0;
}