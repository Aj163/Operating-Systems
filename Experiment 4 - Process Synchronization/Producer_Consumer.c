#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 1000
#define MAX_SEC 1000000 //1 second
#define gotoxy(x, y) printf("%c[%d;%df", 0x1B, x, y)

sem_t mutex, empty, full;
int buffer[N];
int n, front=0, rear=0, cnt=0;

void push(int x)
{
	if(cnt==N)
		return;

	buffer[rear] = x;
	rear = (rear +1)%N;
	cnt++;
}

int pop()
{
	if(cnt==0)
		return -1;

	int ret = buffer[front];
	front = (front +1)%N;
	cnt--;
	return ret;
}

void *produce(void *iterations)
{
	int tim;

	for(int i=0; i<*(int *)iterations; i++)
	{
		//Produce Item
		int item = rand()%N;

		sem_wait(&empty);
		sem_wait(&mutex);

		//CS
		tim = rand()%MAX_SEC;
		usleep(tim);
		//Push Item
		push(item);

		sem_post(&mutex);
		sem_post(&full);

		//NON CS
		gotoxy(i+3, 0);
		printf("Produced item : %d", item);
		gotoxy(5, 60);
		printf("Items in buffer : %2d\n", cnt);
		fflush(stdout);
	}
}

void *consume(void *iterations)
{
	int tim;

	for(int i=0; i<*(int *)iterations; i++)
	{
		int item;

		sem_wait(&full);
		sem_wait(&mutex);

		//CS
		tim = rand()%MAX_SEC;
		usleep(tim);
		//Remove Item
		item = pop();

		sem_post(&mutex);
		sem_post(&empty);

		//NON CS
		gotoxy(i+3, 30);
		printf("Consumed item : %d", item);
		gotoxy(5, 60);
		printf("Items in buffer : %2d\n", cnt);
		fflush(stdout);
	}
}

int main()
{
	system("clear");
	srand(time(0));

	pthread_t producer, consumer;
	int iterations_consume = rand()%10 +6; //(3, 9)
	int iterations_produce = rand()%10 +iterations_consume;

	printf("Enter size of Buffer : ");
	scanf("%d", &n);

	sem_init(&mutex, 0, 1); //Initial Value 1
	sem_init(&empty, 0, n); //Initial value n
	sem_init(&full, 0, 0); //Initial value 0

	pthread_create(&producer, NULL, produce, &iterations_produce);
	pthread_create(&consumer, NULL, consume, &iterations_consume);

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	gotoxy(iterations_produce+4, 0);
}