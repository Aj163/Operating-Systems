#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 100

#define MAX_SEC 3000000 //3 seconds
#define gotoxy(x, y) printf("%c[%d;%df", 0x1B, x, y)

sem_t mutex, db;
int read_cnt = 0;
int n, m;

void *Read(void *arg)
{
	int *id = ((int *)arg);
	int repeat = rand()%5 +1;
	for(int i=0; i<repeat; i++)
	{
		int tim = rand()%MAX_SEC;
		usleep(tim);

		sem_wait(&mutex);
		read_cnt++;
		if(read_cnt == 1)
			sem_wait(&db);
		sem_post(&mutex);

		//CS
		gotoxy(3+ *id, 20);
		printf("Reading");
		fflush(stdout);
		tim = rand()%MAX_SEC;
		usleep(tim);
		gotoxy(3+ *id, 20);
		printf("Idle   ");
		fflush(stdout);

		sem_wait(&mutex);
		read_cnt--;
		if(read_cnt == 0)
			sem_post(&db);
		sem_post(&mutex);
	}
}

void *Write(void *arg)
{
	int *id = ((int *)arg);
	int repeat = rand()%5 +1;
	for(int i=0; i<n; i++)
	{
		int tim = rand()%MAX_SEC;
		usleep(tim);

		sem_wait(&db);

		//CS
		gotoxy(6+n+ *id, 20);
		printf("Writing");
		fflush(stdout);
		tim = rand()%MAX_SEC;
		usleep(tim);
		gotoxy(6+n+ *id, 20);
		printf("Idle   ");
		fflush(stdout);

		sem_post(&db);
	}
}

int main()
{
	system("clear");
	srand(time(0));

	pthread_t reader[N], writer[N];
	int id[N];

	printf("Enter number of readers and writers : ");
	scanf("%d%d", &n, &m);

	sem_init(&mutex, 0, 1);
	sem_init(&db, 0, 1);

	for(int i=0; i<N; i++)
		id[i] = i;

	//Printing
	printf("\nReader");
	gotoxy(3, 20);
	printf("Status\n");
	for(int i=0; i<n; i++)
	{
		printf("%d", i+1);
		gotoxy(4+i, 20);
		printf("Idle\n");
	}

	gotoxy(6+n, 0);
	printf("Writer");
	gotoxy(6+n, 20);
	printf("Status\n");
	for(int i=0; i<m; i++)
	{
		printf("%d", i+1);
		gotoxy(7+n+i, 20);
		printf("Idle\n");
	}

	//Threads
	for(int i=0; i<n; i++)
		pthread_create(reader+i, NULL, Read, id+i+1);
	for(int i=0; i<m; i++)
		pthread_create(writer+i, NULL, Write, id+i+1);

	for(int i=0; i<n; i++)
		pthread_join(reader[i], NULL);
	for(int i=0; i<m; i++)
		pthread_join(writer[i], NULL);

	sem_destroy(&mutex);
	sem_destroy(&db);

	gotoxy(n+m+8, 0);
}