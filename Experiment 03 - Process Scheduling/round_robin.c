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
	int remaining_time;
};

struct process p[N];
int queue[N];
int front = 0, rear = 0;
int n, time_quantum;

void push(int pid)
{
	queue[rear] = pid;
	rear = (rear+1)%N;
}

int pop()
{
	if(front == rear)
		return -1;

	int ret = queue[front];
	front = (front +1)%N;
	return ret;
}

void add_processes(int tim)
{
	for(int i=0; i<n; i++)
		if(p[i].arrival_time == tim)
			push(i);
}

void compute()
{
	int tim=0; //Time
	int tot=n; //Total number of process yet to finish execution
	int pos=-1; //Process under execution
	int local_tim=0; //Time after previous time_quantum
	
	add_processes(tim); //Add processes which have arrived at Time = tim

	printf("\n====================================================================================\n");
	printf("\nOrder of execution\n");

	while(tot)
	{
		if(local_tim == 0) //New time_quantum
		{
			//Put previous process at the end of the queue
			if(pos != -1)
				push(pos);

			//Get next process
			pos = pop();
		}

		printf("%d ", pos==-1? -1:pos+1); //Print process under execution (every second)

		//Update info for other processes
		for(int i=0; i<n; i++)
		{
			if(p[i].arrival_time > tim)
				continue;
			if(i==pos)
				continue;
			if(p[i].remaining_time == 0)
				continue;

			p[i].waiting_time++;
			p[i].turn_around_time++;
		}

		if(pos != -1)
		{
			//Update info for current process
			p[pos].remaining_time--;
			p[pos].turn_around_time++;
			
			if(p[pos].remaining_time == 0)
			{
				//Process complete
				tot--;
				local_tim = -1; //Reset
				pos = -1;
			}
		}
		else
			local_tim = -1; //Reset

		tim++;
		local_tim = (local_tim +1)%time_quantum;
		add_processes(tim);
	}

	printf("\n");
}

int main()
{
	double av_wait = 0.0, av_turn = 0.0;
	system("clear");

	printf("Enter the number of processes and the time quantum : ");
	scanf("%d%d", &n, &time_quantum);

	printf("Enter the arrival and burst time of the processes.\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p[i].arrival_time);
		scanf("%d", &p[i].burst_time);
		p[i].pid = i+1;
		p[i].remaining_time = p[i].burst_time;
	}

	compute();

	printf("\n====================================================================================\n");
	printf("Process\t\tArrival Time\tBurst Time\tWaiting time\tTurn around time\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", p[i].pid, p[i].arrival_time);
		printf("%d\t\t%d\t\t%d\n", p[i].burst_time, p[i].waiting_time, p[i].turn_around_time);

		av_turn += p[i].turn_around_time;
		av_wait += p[i].waiting_time;
	}

	av_turn /= 1.0*n;
	av_wait /= 1.0*n;

	printf("\n====================================================================================\n");
	printf("\nAverage waiting time     : %0.3lf", av_wait);
	printf("\nAverage turn around time : %0.3lf\n\n", av_turn);
	
}

/*

Test Case 1:
3 2
0 1
2 3
4 5

Output:

*/