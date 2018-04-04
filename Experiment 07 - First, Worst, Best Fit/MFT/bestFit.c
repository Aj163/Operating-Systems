#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define N 1000

typedef struct
{
	int pid;
	int size;
	bool allocated;
	int partition;
}process;

typedef struct
{
	int size;
	int allocated;
	int pid;
}partition;

int mm_size, n, m;
process p[N];
partition part[N];

int get_slot(int pid)
{
	int mini = 1e9, pos=-1;
	for(int i=0; i<m; i++)
		if(part[i].pid == -1 && part[i].size >= p[pid].size && mini > part[i].size)
		{
			mini = part[i].size;
			pos = i;
		}

	return pos;
}

void free_slot(int pos)
{
	part[pos].pid = -1;
	part[pos].allocated = 0;
}

int external_fragment()
{
	int ret = 0;
	for(int i=0; i<m ;i++)
		if(part[i].pid == -1)
			ret += part[i].size;

	return ret;
}

int internal_fragment()
{
	int ret = 0;
	for(int i=0; i<m ;i++)
		ret += part[i].size - part[i].allocated;

	return ret;
}

int main()
{
	system("clear");
	int mm_size, n;

	printf("Enter the total size of memory : ");
	scanf("%d", &mm_size);

	printf("Enter number of partitions : ");
	scanf("%d", &m);
	printf("\nEnter the partition sizes\n");
	for(int i=0; i<m; i++)
	{
		scanf("%d", &part[i].size);
		part[i].allocated = 0;
		part[i].pid = -1;
	}

	printf("\nEnter number of processes : ");
	scanf("%d", &n);

	//########################################################################## Allocating N Processes

	printf("Enter size of each process\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p[i].size);
		p[i].pid = i;
		p[i].allocated = false;
		p[i].partition = -1;

		int pos = get_slot(i);
		if(pos == -1)
			continue;

		part[pos].allocated = p[i].size;
		part[pos].pid = i;
		p[i].allocated = true;
		p[i].partition = pos;
	}

	//########################################################################## Printing

	bool flag = 0;
	printf("\nProcess\t\tSize\t\tAllocated\tPartition\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", i+1, p[i].size);
		if(p[i].allocated)
			printf("Yes\t\t");
		else
		{
			flag = 1;
			printf("No\t\t");
		}

		if(p[i].partition == -1)
			printf("None\n");
		else
			printf("%d\n", p[i].partition +1);
	}

	if(flag)
		printf("\nExternal Fragmentation : %d\n", external_fragment());

	//########################################################################## New Process Arrives

	printf("\n\nEnter new process size : ");
	scanf("%d", &p[n].size);
	p[n].pid = n;
	p[n].allocated = false;
	p[n].partition = -1;

	int pos = get_slot(n);
	if(pos == -1)
	{
		int prem;
		printf("\nNo partition available\n");
		printf("Which process would you like to remove? ");

		scanf("%d", &prem);
		prem--;
		free_slot(p[prem].partition);

		pos = get_slot(n);
		if(pos == -1)
		{
			printf("\nStill not enough memory\n");
			printf("\nInternal Fragments : %d\n", internal_fragment());
			printf("External Fragments : %d\n\n", external_fragment());
			return 0;
		}
	}

	part[pos].allocated = p[n].size;
	part[pos].pid = n;
	p[n].allocated = true;
	p[n].partition = pos;
	
	//########################################################################## Memory Table
	printf("\n\nMemory Table\nPartition\tSize\t\tAllocated\tProcess\n");
	for(int i=0; i<m; i++)
	{
		printf("%d\t\t%d\t\t%d\t\t", i+1, part[i].size, part[i].allocated);
		if(part[i].pid == -1)
			printf("None\n");
		else
			printf("%d\n", part[i].pid+1);
	}

	printf("\nInternal Fragments : %d\n\n", internal_fragment());
}

/*

-------------------Test Case 1-----------------------
1000 4
100
200
300
400
5
50
25
350
250
100
101
2

---------------------Output------------------------
Process		Size		Allocated	Partition
1		50		Yes		1
2		25		Yes		2
3		350		Yes		4
4		250		Yes		3
5		100		No		None

External Fragmentation : 0


Memory Table
Partition	Size		Allocated	Process
1		100		50		1
2		200		101		6
3		300		250		4
4		400		350		3

Internal Fragments : 249


-------------------Test Case 2-----------------------
1000 4
100
200
300
400
5
50
25
350
250
100
101
1

---------------------Output------------------------
Process		Size		Allocated	Partition
1		50		Yes		1
2		25		Yes		2
3		350		Yes		4
4		250		Yes		3
5		100		No		None

External Fragmentation : 0

Still not enough memory

Internal Fragments : 375
External Fragments : 100

*/