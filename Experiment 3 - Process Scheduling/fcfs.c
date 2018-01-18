//FCFS Process Scheduling

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	double av_wait = 0, av_turn = 0;
	int n, wait = 0, turn = 0;
	int burst_time[100];

	printf("\nEnter the number of processes : ");
	scanf("%d", &n);

	printf("Enter the burst time of the processes.\n");
	for(int i=0; i<n; i++)
		scanf("%d", burst_time+i);

	printf("\n");
	printf("Process\t\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		turn += burst_time[i];
		av_wait += wait;
		av_turn += turn;
		printf("%d\t\t%d\t\t%d\t\t%d\n", i+1, burst_time[i], wait, turn);
		wait += burst_time[i];
	}

	av_turn /= 1.0*n;
	av_wait /= 1.0*n;

	printf("\nAverage waiting time     : %0.3lf", av_wait);
	printf("\nAverage turn around time : %0.3lf", av_turn);
	printf("\n\n");
}