//FCFS Process Scheduling

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b)
{
	if(a<b)
		return a;
	return b;
}

int main()
{
	double av_wait = 0, av_turn = 0, tot;
	int n, wait = 0, turn = 0, tim = 0, time_quantum;
	int burst_time[100], waiting_time[100] = {0}, turn_around_time[100], b_time[100];

	printf("\nEnter the number of processes and time quantum: ");
	scanf("%d%d", &n, &time_quantum);

	printf("Enter the burst time of the processes.\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", burst_time+i);
		b_time[i] = burst_time[i];
	}

	tot = n;
	while(tot)
	{
		for(int i=0; i<n ;i++)
		{
			if(burst_time[i] == 0)
				continue;

			int reduce = min(time_quantum, burst_time[i]);
			burst_time[i] -= reduce;
			tim += reduce;

			for(int j=0; j<n; j++)
				if(i!=j && burst_time[j])
					waiting_time[j] += reduce;


			if(burst_time[i] == 0)
			{
				tot--;
				turn_around_time[i] = tim; 
			}
		}
	}

	printf("\n");
	printf("Process\t\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		av_turn += turn_around_time[i];
		av_wait += waiting_time[i];
		printf("%d\t\t%d\t\t%d\t\t%d\n", i+1, b_time[i], waiting_time[i], turn_around_time[i]);
	}

	av_turn /= 1.0*n;
	av_wait /= 1.0*n;

	printf("\nAverage waiting time     : %0.3lf", av_wait);
	printf("\nAverage turn around time : %0.3lf", av_turn);
	printf("\n\n");
}