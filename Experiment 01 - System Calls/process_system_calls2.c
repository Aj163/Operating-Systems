#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void main()
{
	pid_t cpid;
	int f = fork();
	if (f == 0)
		exit(0);		/* terminate child */
	else
		cpid = wait(NULL);
	
	fork();
	printf("\nThis process has been forked.\n");

	printf("Opening gedit...\n\n");
	execlp("gedit", "text.txt", NULL);
}