#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 1000

int invalidInput(int pageTable[], int siz, int maxValue)
{
	for(int i=0; i<siz; i++)
		if(pageTable[i] < -1 || pageTable[i]>=maxValue)
			return 1;

	//Check for duplicates
	for(int i=0; i<siz; i++)
		if(pageTable[i] != -1)
		{
			for(int j=i+1; j<siz; j++)
				if(pageTable[j] == pageTable[i])
					return 1;
		}

	return 0;
}

int main()
{
	system("clear");
	int pageSize, mainMemorySize, virtualAddress, physicalAddress, virtualAddressSize;
	char ch;
	int pageTable[N];

	printf("Enter page size in bits : ");
	scanf("%d", &pageSize);

	printf("Enter size of main memory in bits: ");
	scanf("%d", &mainMemorySize);

	printf("Enter virtual address size in bits: ");
	scanf("%d", &virtualAddressSize);

	printf("\nEnter page table (-1 if page doesn't exist)\n");
	printf("Page\tFrame\n");
	for(int i=0; i<virtualAddressSize/pageSize; i++)
	{
		printf("%d\t", i);
		scanf("%d", &pageTable[i]);

		while(invalidInput(pageTable, i+1, mainMemorySize/pageSize))
		{
			printf("Invalid Input. Try again\n");
			printf("%d\t", i);
			scanf("%d", &pageTable[i]);
		}
	}

	do
	{
		printf("\nEnter virtual address : ");
		scanf("%d", &virtualAddress);

		physicalAddress = virtualAddress%pageSize + pageTable[virtualAddress/pageSize]*pageSize;
		if(pageTable[virtualAddress/pageSize] == -1)
			printf("Page Fault\n");
		else
			printf("Physical Address : %d\n", physicalAddress);

		printf("\nDo you want to continue ? (y/n) ");
		getchar();
		ch = getchar();
	}while(ch == 'y' || ch == 'Y');
}

/*

Test Case:
100 500 1000
2 3 -1 0 4 -1 -1 1 -1 -1
5 y
205 y
705 n

Output:
205
Page Fault
105

*/