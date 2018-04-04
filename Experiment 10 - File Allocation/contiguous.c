#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100000

typedef struct
{
	int id;
	int size;
}file;

int blocks[N];
file queue[N];
int n, diskCapacity, blockCapacity, front = 0, rear = -1;

int ceilDivision(int a, int b){
	return a/b + (a%b != 0);
}

void printDisk()
{
	printf("\n-------Disk-----\n");
	for(int i=0; i<n; i++)
	{
		if(blocks[i] == -1)
			printf("# ");
		else
			printf("%d ", blocks[i]);
	}
	printf("\n----------------\n");
}

int findStartBlock(int siz)
{
	int i=0, flag;
	while(i<n)
	{
		if(blocks[i] != -1)
		{
			i++;
			continue;
		}

		flag = 1;
		for(int j=i; j<siz+i; j++)
			if(blocks[j] != -1 || j==n)
			{
				flag = 0;
				i = j;
				break;
			}

		if(flag)
			return i;

		i++;
	}

	return -1;
}

int externalFragmentation()
{
	int ret = 0;
	for(int i=0; i<n; i++)
		if(blocks[i] == -1)
			ret++;

	return ret;
}

void insertFilesFromQueue()
{
	for(int i=front; i<=rear; i++)
	{
		int pos = findStartBlock(queue[i].size);
		if(pos == -1)
		{
			if(externalFragmentation() >= queue[i].size)
				printf("F%d : External Fragmentation : %d\n", queue[i].id, externalFragmentation()*blockCapacity);
			else
				printf("F%d : Not enough memory\n", queue[i].id);
		}
		else
		{
			for(int j=pos; j<pos+queue[i].size; j++)
				blocks[j] = queue[i].id;

			for(int j=i-1; j>=front; j--)
				queue[j+1] = queue[j];
			front++;
		}
	}
}

int main()
{
	system("clear");
	int ch;

	printf("Enter Disk Capacity : ");
	scanf("%d", &diskCapacity);

	printf("Enter Block Capacity : ");
	scanf("%d", &blockCapacity);

	n = diskCapacity/blockCapacity;
	for(int i=0; i<n; i++)
		blocks[i] = -1;

	do
	{
		printf("\nEnter your choice (1. Add File, 2. Remove File, 3. Search) : ");
		scanf("%d", &ch);

		if(ch == 1)
		{
			int id, siz;
			printf("\nEnter file ID : ");
			scanf("%d", &id);

			printf("Enter file size : ");
			scanf("%d", &siz);

			siz = ceilDivision(siz, blockCapacity);
			int pos = findStartBlock(siz);
			if(pos == -1)
			{
				file f = {id, siz};
				queue[++rear] = f;

				if(externalFragmentation() >= siz)
					printf("F%d : External Fragmentation : %d\n", id, externalFragmentation()*blockCapacity);
				else
					printf("F%d : Not enough memory\n", id);
			}
			else
			{
				for(int i=pos; i<pos+siz; i++)
					blocks[i] = id;
			}
		}
		else if(ch == 2)
		{
			int id;
			printf("\nEnter file id to remove : ");
			scanf("%d", &id);

			for(int i=0; i<n; i++)
				if(blocks[i] == id)
					blocks[i] = -1;

			insertFilesFromQueue();
		}
		else if(ch == 3)
		{
			int id;
			printf("\nEnter file id to search for : ");
			scanf("%d", &id);

			int flag = 0;
			for(int i=0; i<n; i++)
				flag += (blocks[i] == id);

			if(!flag)
				printf("File not found in Disk\n");
			else
			{
				printf("Blocks in which F%d is present in\n", id);
				for(int i=0; i<n; i++)
					if(blocks[i] == id)
						printf("%d ", i);
				printf("\n");
			}
		}

		printDisk();
	}while(ch >= 1 && ch <= 3);
}