//Priority Process Scheduling
//Pre-emptive
//Min Priority

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

struct process
{
	int pid;
	int priority;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

struct process p[N];
double av_wait = 0.0, av_turn = 0.0;
int n, burst[N];

void compute()
{
	int tim=-1, tot=n, mini=1e9, pos=-1, curr=-1;

	while(tot)
	{
		tim++;
		mini = 1e9;
		pos = -1;

		for(int i=0; i<n; i++)
			if(mini > p[i].priority && burst[i] && tim>=p[i].arrival_time)
			{
				pos = i;
				mini = p[i].priority;
			}

		if(curr != -1)
			pos = curr;

		if(pos == -1)
			continue;

		curr = pos;

		burst[pos]--;
		for(int i=0; i<n; i++)
			if(i!=pos && burst[i] && tim>=p[i].arrival_time)
				p[i].waiting_time++;

		if(burst[pos] == 0)
		{
			tot--;
			curr = -1;
			p[pos].turn_around_time = tim - p[pos].arrival_time +1;

			av_turn += p[pos].turn_around_time;
			av_wait += p[pos].waiting_time;
		}
	}
}

int main()
{
	system("clear");
	printf("Enter the number of processes : ");
	scanf("%d", &n);

	printf("Enter the arrival time of the processes.\n");
	for(int i=0; i<n; i++)
		scanf("%d", &p[i].arrival_time);

	printf("Enter the priority of the processes.\n");
	for(int i=0; i<n; i++)
		scanf("%d", &p[i].priority);

	printf("Enter the burst time of the processes.\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p[i].burst_time);
		p[i].pid = i+1;
		burst[i] = p[i].burst_time;
	}

	compute();

	printf("\n");
	printf("Process\t\tPriority\tArrival Time\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t%d\t\t", p[i].pid, p[i].priority, p[i].arrival_time);
		printf("%d\t\t%d\t\t%d\n", p[i].burst_time, p[i].waiting_time, p[i].turn_around_time);
	}

	av_turn /= 1.0*n;
	av_wait /= 1.0*n;

	printf("\nAverage waiting time     : %0.3lf", av_wait);
	printf("\nAverage turn around time : %0.3lf", av_turn);
	printf("\n\n");
}

/*

--------------------------- Test Case 1 -----------------------------------
3
0 1 4
8 3 1
8 3 1

------------------------------ Output -------------------------------------
Process		Arrival Time	Burst Time	Waiting time	Turn around time
1			0				8			0				8
2			1				3			8				11
3			4				1			4				5

Average waiting time     : 4.000
Average turn around time : 8.000
---------------------------------------------------------------------------

*/