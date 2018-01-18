#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum)
{
	printf("Caught signal %d, coming out...\n", signum);
	exit(1);
}

void main()
{
	signal(SIGINT, sighandler);

	while(1)
	{
		printf("Going to sleep for a second... Press ctrl+c\n");
		sleep(1);
	}
}