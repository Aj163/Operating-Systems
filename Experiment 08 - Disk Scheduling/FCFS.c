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
	int request[N];

	printf("Enter number of requests : ");
	scanf("%d", &n);

	printf("Enter current track position : ");
	scanf("%d", &request[0]);

	printf("\nEnter the requests\n");
	for(int i=1; i<=n; i++)
		scanf("%d", &request[i]);
	n++;

	int ans = 0;
	printf("\nHead movement\n");
	for(int i=1; i<n; i++)
	{
		printf("%d -> %d : %d\n", request[i-1], request[i], abs(request[i] - request[i-1]));
		ans += abs(request[i] - request[i-1]);
	}

	printf("\nTotal Head Movement : %d\n\n", ans);
}

/*

===========Test Case===============
6 20
53 14 86 37 123 168

============Output=================
Head movement
20 -> 53
53 -> 14
14 -> 86
86 -> 37
37 -> 123
123 -> 168

Total Head Movement : 324

*/