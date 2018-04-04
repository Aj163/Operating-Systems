#include <stdio.h>
#include <stdlib.h>

#define N 1000

int abs(int a)
{
	if(a>0)
		return a;
	return -a;
}

int main()
{
	system("clear");
	int n;
	int request[N], done[N] = {0};

	printf("Enter number of requests : ");
	scanf("%d", &n);

	printf("Enter current track position : ");
	scanf("%d", &request[0]);

	printf("\nEnter the requests\n");
	for(int i=1; i<=n; i++)
		scanf("%d", &request[i]);
	n++;

	int ans = 0, prev = request[0];
	done[0] = 1;

	printf("\nHead movement\n");
	for(int i=1; i<n; i++)
	{
		int nextRequest, mini = 1e9;
		for(int j=1; j<n; j++)
			if(done[j] == 0 && abs(request[j] - prev) < mini)
			{
				mini = abs(prev - request[j]);
				nextRequest = j;
			}

		done[nextRequest] = 1;
		ans += mini;
		printf("%d -> %d\n", prev, request[nextRequest]);
		prev = request[nextRequest];
	}

	printf("\nTotal Head Movement : %d\n\n", ans);
}

/*

===========Test Case===============
6 58
53 14 86 37 123 168

============Output=================
Head movement
58 -> 53
53 -> 37
37 -> 14
14 -> 86
86 -> 123
123 -> 168

Total Head Movement : 198

*/