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
}process;

typedef struct
{
	int pid; //-1 if free
	int size;
}slots;

process p[N];
slots s[N];
int mm_size, n, tot;

int external_fragment()
{
	int ret = 0;
	for(int i=0; i<tot; i++)
		if(s[i].pid == -1)
			ret += s[i].size;

	return ret;
}

void insert(int pos, int pid)
{
	for(int i=tot; i>pos; i--)
		s[i] = s[i-1];

	s[pos].pid = pid;
	s[pos].size = p[pid].size;
	p[pid].allocated = true;

	s[pos+1].size -= p[pid].size;
	tot++;
}

int get_slot(int pid)
{
	for(int i=0; i<tot; i++)
		if(s[i].pid == -1 && s[i].size >= p[pid].size)
			return i;

	return -1;
}

int free_slot(int pos)
{
	s[pos].pid=-1;

	if(pos!=tot-1 && s[pos+1].pid==-1)
	{
		s[pos].size += s[pos+1].size;
		for(int i=pos+1; i<tot-1; i++)
			s[i] = s[i+1];

		tot--;
	}

	if(pos>0 && s[pos-1].pid==-1)
	{
		s[pos-1].size += s[pos].size;
		for(int i=pos; i<tot-1; i++)
			s[i] = s[i+1];

		tot--;
	}
}

int main()
{
	system("clear");
	int mm_size, n;

	printf("Enter the total size of memory : ");
	scanf("%d", &mm_size);

	tot=1;
	s[0].pid = -1;
	s[0].size = mm_size;

	printf("Enter number of processes : ");
	scanf("%d", &n);

	//########################################################################## Allocating N Processes

	printf("\nEnter size of each process\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p[i].size);
		p[i].pid = i;
		p[i].allocated = false;

		int pos = get_slot(i);
		if(pos == -1)
			continue;

		if(s[pos].size == p[i].size)
		{
			p[i].allocated = true;
			s[pos].pid = i;
		}
		else
			insert(pos, i);
	}

	//########################################################################## Printing

	bool flag = 0;
	printf("\nProcess\t\tSize\t\tAllocated\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t%d\t\t", i+1, p[i].size);
		if(p[i].allocated)
			printf("Yes\n");
		else
		{
			flag = 1;
			printf("No\n");
		}
	}

	if(flag)
		printf("\nExternal Fragmentation : %d\n", external_fragment());

	//########################################################################## New Process Arrives

	printf("\n\nEnter new process size : ");
	scanf("%d", &p[n].size);
	p[n].pid = n;
	p[n].allocated = false;

	int pos = get_slot(n);
	if(pos == -1)
	{
		int prem;
		printf("\nNot enough contiguous memory to allocate memory to process\n");
		printf("Which process would you like to remove? ");

		scanf("%d", &prem);
		prem--;
		for(int i=0; i<tot; i++)
			if(s[i].pid == prem)
				free_slot(i);

		pos = get_slot(n);
		if(pos == -1)
		{
			printf("\nStill not enough memory\n");
			printf("External Fragments : %d\n\n", external_fragment());
			return 0;
		}
	}

	if(s[pos].size == p[n].size)
	{
		p[n].allocated = true;
		s[pos].pid = n;
	}
	else
		insert(pos, n);
	
	//########################################################################## Memory Table
	printf("\n\nMemory Table\nSize\t\tProcess\n");
	for(int i=0; i<tot; i++)
	{
		printf("%d\t\t", s[i].size);
		if(s[i].pid == -1)
			printf("None\n");
		else
			printf("%d\n", s[i].pid+1);
	}
}

/*

-------------------Test Case 1-----------------------
1000 7
100
200
300
300
150
20
60
20

---------------------Output------------------------
Process		Size		Allocated
1		100		Yes
2		200		Yes
3		300		Yes
4		300		Yes
5		150		No
6		20		Yes
7		60		Yes

External Fragmentation : 20

Memory Table
Size		Process
100		1
200		2
300		3
300		4
20		6
60		7
20		8


-------------------Test Case 2-----------------------
1000 7
100
200
300
300
150
20
60
150
2

---------------------Output------------------------
Process		Size		Allocated
1		100		Yes
2		200		Yes
3		300		Yes
4		300		Yes
5		150		No
6		20		Yes
7		60		Yes

External Fragmentation : 20

Memory Table
Size		Process
100		1
150		8
50		None
300		3
300		4
20		6
60		7
20		None


-------------------Test Case 3-----------------------
1000 7
100
200
300
300
150
20
60
150
1

---------------------Output------------------------
Process		Size		Allocated
1		100		Yes
2		200		Yes
3		300		Yes
4		300		Yes
5		150		No
6		20		Yes
7		60		Yes

External Fragmentation : 20

Still not enough memory
External Fragments : 120

*/