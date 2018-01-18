#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

void main()
{
	pid_t pid = getpid();
	printf("\nKilling process with PID : %d\n", pid);
	kill(pid, 0);

	char *directory = "/home/nitk/Desktop";
	chdir(directory);
	printf("\nDirectory changed to %s\n\n", directory);
}