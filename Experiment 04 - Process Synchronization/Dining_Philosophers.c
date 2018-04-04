#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define N 100
#define MAX_SEC 3000000 //3 seconds
#define gotoxy(x, y) printf("%c[%d;%df", 0x1B, x, y)

sem_t stick[N], mutex;
int n;

void *eat(void *arg)
{
	int id = *((int *)arg);
	int iterations = rand()%5 +1;

	for(int i=0; i<iterations; i++)
	{
		int tim = rand()%MAX_SEC;
		//usleep(tim);

		if(id%2 == 0)
		{
			sem_wait(stick+id);
			sem_wait(stick+(id+1)%n);
		}
		else
		{
			sem_wait(stick+(id+1)%n);
			sem_wait(stick+id);
		}	

		//CS
		sem_wait(&mutex);
		gotoxy(4+id, 20);
		printf("Eating  ");
		fflush(stdout);
		sem_post(&mutex);
		tim = rand()%MAX_SEC;
		usleep(tim);
		gotoxy(4+id, 20);
		printf("Thinking");
		fflush(stdout);

		sem_post(stick+id);
		sem_post(stick+(id+1)%n);
	}
}

int main()
{
	system("clear");
	srand(time(0));

	int id[N];
	pthread_t phil[N];

	printf("Enter the number of philosophers : ");
	scanf("%d", &n);

	printf("\nPhilosopher");
	gotoxy(3, 20);
	printf("Status\n");
	for(int i=0; i<n; i++)
	{
		printf("%d", i+1);
		gotoxy(4+i, 20);
		printf("Thinking\n");
	}

	sem_init(&mutex, 0, 1);
	for(int i=0; i<N; i++)
		id[i] = i;
	for(int i=0; i<n; i++)
		sem_init(stick+i, 0, 1);
	for(int i=0; i<n; i++)
		pthread_create(phil+i, NULL, eat, id+i);

	for(int i=0; i<n; i++)
		pthread_join(phil[i], NULL);
	for(int i=0; i<n; i++)
		sem_destroy(stick+i);

	gotoxy(5+n, 0);
}