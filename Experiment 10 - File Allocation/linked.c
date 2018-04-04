#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100000

typedef struct
{
	int id;
	int size;
}file;

typedef struct
{
	int fid;
	int next;
}Block;

Block blocks[N];
file queue[N];
int n, diskCapacity, blockCapacity, front = 0, rear = -1;

int ceilDivision(int a, int b){
	return a/b + (a%b != 0);
}

int freeMemory()
{
	int ret = 0;
	for(int i=0; i<n; i++)
		if(blocks[i].fid == -1)
			ret++;
	return ret;
}

void printDisk()
{
	printf("\n-------Disk-----\n");
	for(int i=0; i<n; i++)
	{
		if(blocks[i].fid == -1)
			printf("#|");
		else
			printf("%d|", blocks[i].fid);

		if(blocks[i].next == -1)
			printf("#  ");
		else
			printf("%d  ", blocks[i].next);
	}
	printf("\n----------------\n");
}

int freeSlot()
{
	for(int i=0; i<n; i++)
		if(blocks[i].fid == -1)
			return i;
}

void insertFilesFromQueue()
{
	for(int i=front; i<=rear; i++)
	{
		if(freeMemory() < queue[i].size)
			printf("F%d : Not enough memory\n", queue[i].id);
		else
		{
			int prev = freeSlot();
			blocks[prev].fid = queue[i].id;

			int siz = queue[i].size;
			siz--;
			while(siz--)
			{
				int pos = freeSlot();
				blocks[prev].next = pos;
				blocks[pos].fid = queue[i].id;
				prev = pos;
			}

			blocks[prev].next = -1;
		}
	}
}

void updateBlockCapacity()
{
	int p=0;
	while((1<<p) < n)
		p++;

	p = ceilDivision(p, 8); //Bytes
	blockCapacity -= p;
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
	updateBlockCapacity();

	for(int i=0; i<n; i++)
	{
		blocks[i].fid = -1;
		blocks[i].next = -1;
	}

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

			if(freeMemory() < siz)
			{
				file f = {id, siz};
				queue[++rear] = f;
				
				printf("F%d : Not enough memory\n", id);
			}
			else
			{
				int prev = freeSlot();
				blocks[prev].fid = id;

				siz--;
				while(siz--)
				{
					int pos = freeSlot();
					blocks[prev].next = pos;
					blocks[pos].fid = id;
					prev = pos;
				}

				blocks[prev].next = -1;
			}
		}
		else if(ch == 2)
		{
			int id;
			printf("\nEnter file id to remove : ");
			scanf("%d", &id);

			for(int i=0; i<n; i++)
				if(blocks[i].fid == id)
				{
					blocks[i].fid = -1;
					blocks[i].next = -1;
				}

			insertFilesFromQueue();
		}
		else if(ch == 3)
		{
			int id;
			printf("\nEnter file id to search for : ");
			scanf("%d", &id);

			int flag = 0;
			for(int i=0; i<n; i++)
				flag += (blocks[i].fid == id);

			if(!flag)
				printf("File not found in Disk\n");
			else
			{
				printf("Blocks in which F%d is present in\n", id);

				int t;
				for(int i=0; i<n; i++)
					if(blocks[i].fid == id)
					{
						t = i;
						break;
					}

				while(blocks[t].next != -1)
				{
					printf("%d ", t);
					t = blocks[t].next;
				}
				printf("%d\n", t);
			}
		}

		printDisk();
	}while(ch >= 1 && ch <= 3);
}