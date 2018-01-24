//Round Process Scheduling
//Pre-emptive

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

struct process
{
	int pid;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

struct process p[N];
double av_wait = 0.0, av_turn = 0.0;
int n, time_quantum, burst[N];

int max(int a, int b)
{
	if(a>b)
		return a;
	return b;
}

void swap(int i, int j)
{
	struct process temp;
	temp = p[i];
	p[i] = p[j];
	p[j] = temp;

	int temp2 = burst[i];
	burst[i] = burst[j];
	burst[j] = temp2;
}

void sort()
{
	for(int i=0; i<n-1; i++)
		for(int j=i+1; j<n; j++)
			if(p[i].arrival_time > p[j].arrival_time)
				swap(i, j);
}

void compute()
{
	int tim=-1, tot=n, pos=-1, prev=-1, local_tim=-1;

	while(tot)
	{
		tim++;
		local_tim++;
		pos = -1;

		if(prev!=-1 && burst[prev] && local_tim != time_quantum)
			pos = prev;
		else
		{
			if(local_tim == time_quantum)
				local_tim = 0;

			int flag=1;
			for(int i=(prev+1)%n; i<n; i++)
				if(burst[i] && tim>=p[i].arrival_time)
				{
					pos = i;
					flag = 0;
					break;
				}

			if(flag)
			{
				for(int i=0; i<=prev; i++)
					if(burst[i] && tim>=p[i].arrival_time)
					{
						
						pos = i;
						break;
					}
			}
		}

		if(pos == -1)
		{
			local_tim = -1;
			continue;
		}

		prev = pos;

		burst[pos]--;
		for(int i=0; i<n; i++)
			if(i!=pos && burst[i] && tim>=p[i].arrival_time)
				p[i].waiting_time++;

		if(burst[pos] == 0)
		{
			tot--;
			local_tim = -1;
			p[pos].turn_around_time = tim - p[pos].arrival_time +1;

			av_turn += p[pos].turn_around_time;
			av_wait += p[pos].waiting_time;
		}
	}
}

int main()
{
	system("clear");
	printf("Enter the number of processes and the time quantum : ");
	scanf("%d%d", &n, &time_quantum);

	printf("Enter the arrival time of the processes.\n");
	for(int i=0; i<n; i++)
		scanf("%d", &p[i].arrival_time);

	printf("Enter the burst time of the processes.\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p[i].burst_time);
		p[i].pid = i+1;
		burst[i] = p[i].burst_time;
	}

	sort();
	compute();

	printf("\n");
	printf("Process\t\tArrival Time\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", p[i].pid, p[i].arrival_time);
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
3 2
0 1 4
8 3 1

------------------------------ Output -------------------------------------
Process		Arrival Time	Burst Time	Waiting time	Turn around time
1			0				8			4				12
2			1				3			4				7
3			4				1			0				1

Average waiting time     : 2.667
Average turn around time : 6.667
---------------------------------------------------------------------------

4 2
3 2 0 4
8 3 2 6

*/