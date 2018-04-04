//Banker's Algorithm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100

typedef struct 
{
	int max;
	int need;
	int allocated;
	int available;
}table;

int main()
{
	system("clear");

	int n, m, p, a[N];
	table t[N][N];
	int total[N], done[N];

	printf("Enter number of processes : ");
	scanf("%d", &n);

	printf("Enter number of types of resources : ");
	scanf("%d", &m);

	printf("Enter total available resources of all types\n");
	for(int i=0; i<m; i++)
		scanf("%d", total+i);

	printf("\nEnter for each process the number of resources needed at max,\n");
	printf("and that currently available for each type\n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
			scanf("%d", &t[i][j].max);
		for(int j=0; j<m; j++)
		{
			scanf("%d", &t[i][j].allocated);
			t[i][j].need = t[i][j].max - t[i][j].allocated;
			total[j] -= t[i][j].allocated;
		}

		done[i]=0;
	}

	printf("Enter process id and request : ");
	scanf("%d", &p);
	p--;
	int fl=1;
	for(int i=0; i<m; i++)
	{
		scanf("%d", a+i);
		if(a[i] > t[p][i].need)
			fl=0;
	}
	if(fl)
	{
		for(int i=0; i<m; i++)
		{
			total[i] -= a[i];
			t[p][i].allocated += a[i];
			t[p][i].need -= a[i];
		}
	}
	else
	{
		printf("\n\nRequest not granted!!\n\n");
		return 0;
	}

	printf("\n\nOrder of execution : ");

	for(int z=0; z<n; z++)
	{
		int pos=-1;
		for(int j=0; j<n; j++)
		{
			int flag=1;
			for(int k=0; k<m; k++)
				if(total[k] < t[j][k].need)
				{
					flag=0;
					break;
				}

			if(flag && done[j] != 1)
			{
				pos=j;
				break;
			}
		}

		printf("%d ", pos+1);

		if(pos==-1)
			break;

		done[pos]=1;
		for(int j=0; j<m; j++)
		{
			t[pos][j].available = total[j];
			total[j] += t[pos][j].allocated;
		}
	}

	printf("\n\nProcess\t\tAvailable Resources\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t", i+1);
		if(done[i]==0)
		{
			printf("Never allocated resources\n");
			continue;
		}

		for(int j=0; j<m; j++)
			printf("%d ", t[i][j].available);
		printf("\n");
	}
	printf("\n");
}

/*

Test Case:
5 3
10 5 7
7 5 3 0 1 0
3 2 2 2 0 0
9 0 2 3 0 2
2 2 2 2 1 1
4 3 3 0 0 2
3 3 3 0



6 4 1
1 2 2
6 0 0
0 1 1
4 3 1

Output:

*/