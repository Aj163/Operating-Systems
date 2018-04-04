//SJF Process Scheduling

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct process
{
	int pid;
	int burst_time;
}processes[100];

void swap(int i, int j)
{
	int t1, t2;

	t1 = processes[i].pid;
	t2 = processes[i].burst_time;

	processes[i].pid = processes[j].pid;
	processes[i].burst_time = processes[j].burst_time;

	processes[j].pid = t1;
	processes[j].burst_time = t2;
}

void sort(int n)
{
	for(int i=0; i<n-1; i++)
		for(int j=i+1; j<n; j++)
			if(processes[i].burst_time > processes[j].burst_time)
				swap(i, j);
}

int main()
{
	double av_wait = 0, av_turn = 0;
	int n, wait = 0, turn = 0, temp;

	printf("\nEnter the number of processes : ");
	scanf("%d", &n);

	printf("Enter the burst time of the processes.\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &temp);
		processes[i].pid = i+1;
		processes[i].burst_time = temp;
	}

	sort(n);

	printf("\n");
	printf("Process\t\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		turn += processes[i].burst_time;
		av_wait += wait;
		av_turn += turn;
		printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, wait, turn);
		wait += processes[i].burst_time;
	}

	av_turn /= 1.0*n;
	av_wait /= 1.0*n;

	printf("\nAverage waiting time     : %0.3lf", av_wait);
	printf("\nAverage turn around time : %0.3lf", av_turn);
	printf("\n\n");
}