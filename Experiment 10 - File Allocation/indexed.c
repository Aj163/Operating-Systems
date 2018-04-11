#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 1000

typedef struct
{
	int id;
	int size;
}file;

typedef struct
{
	int fid; //-1 if free
	int metaData;
		//0 - File contents
		//1 - Meta Data
	int entries[100];
}Block;

Block blocks[N];
file queue[N];
int n, diskCapacity, blockCapacity, front = 0, rear = -1, entriesPerBlock;

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
		if(blocks[i].metaData)
			printf(" @%d ", blocks[i].fid);
		else
			printf("  %d ", blocks[i].fid);
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
		if(freeMemory() < queue[i].size +1)
			printf("F%d : Not enough memory\n", queue[i].id);
		else
		{
			int p = freeSlot();
			blocks[p].fid = queue[i].id;
			blocks[p].metaData = 1;
			int curr = 0;

			int siz = queue[i].size;
			while(siz--)
			{
				int pos = freeSlot();
				blocks[pos].fid = queue[i].id;
				blocks[pos].metaData = 0;
				blocks[p].entries[curr++] = pos;
			}

			blocks[p].entries[curr] = -1;
		}
	}
}

void updateBlockCapacity()
{
	int p=0;
	while((1<<p) < n)
		p++;

	entriesPerBlock = blockCapacity/ceilDivision(p, 8);
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
		blocks[i].metaData = 0;
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
				int p = freeSlot();
				blocks[p].fid = id;
				blocks[p].metaData = 1;
				int curr = 0;

				while(siz--)
				{
					int pos = freeSlot();
					blocks[pos].fid = id;
					blocks[pos].metaData = 0;
					blocks[p].entries[curr++] = pos;
				}

				blocks[p].entries[curr] = -1;
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
					blocks[i].metaData = 0;
				}

			insertFilesFromQueue();
		}
		else if(ch == 3)
		{
			int id;
			printf("\nEnter file id to search for : ");
			scanf("%d", &id);

			int flag = -1;
			for(int i=0; i<n; i++)
				if(blocks[i].fid == id && blocks[i].metaData == 1)
				{
					flag = i;
					break;
				}

			if(flag == -1)
				printf("File not found in Disk\n");
			else
			{
				printf("Metadata of blocks for F%d is present in block %d\n", id, flag);
				printf("Contents of Metedata block : ");

				int curr = 0;
				while(blocks[flag].entries[curr] != -1)
					printf("%2d ", blocks[flag].entries[curr++]);
				printf("-1\n");
			}
		}

		printDisk();
	}while(ch >= 1 && ch <= 3);
}
