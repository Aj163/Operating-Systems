#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
	printf("\nUID : %d\nEUID: %d\nPID : %d\n", getuid(), geteuid(), getpid());
	printf("PPID : %d\nGID : %d\nEGID : %d\n\n", getppid(), getgid(), getegid());

	printf("Alarm clock for 5 seconds...\n");
	alarm(5);

	printf("Exiting the program after alarm clock...\n");
	sleep(5);

	exit(0);
}