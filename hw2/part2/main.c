#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
sem_t mutex;
sem_t s[N];

void* philosopher(void* target);
void think(int i);
void take_forks(int i);
void put_forks(int i);
void test(int i);


void* philosopher(void* target)
{
	while(1)
	{
		int* i = target;
		think(*i);
		take_forks(*i);
		put_forks(*i);
	}
}

void think(int i)
{
	printf("Philosopher %d is thinking.\n",i);
	sleep(1);
}

void take_forks(int i)
{
	sem_wait(&mutex);
	state[i] = HUNGRY;
	printf("Philosopher %d is Hungry.\n", i);
	test(i);
	sem_post(&mutex);
	sem_wait(&s[i]);
	sleep(1);
}

void put_forks(int i)
{
	sem_wait(&mutex);
	state[i] = THINKING;
	printf("Philosopher %d puts fork %d and %d down.\n",i,LEFT,i);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void test(int i)
{
	if(state[i] == HUNGRY && state[LEFT]!=EATING && state[RIGHT] != EATING)
	{
		state[i] = EATING;
		printf("Philosopher %d takes fork %d and %d up.\n",i,LEFT,i);
		printf("Philosopher %d is eating.\n",i);
		sem_post(&s[i]);
	}
}

int main()
{
	int i;
	pthread_t thread[N];
	
	sem_init(&mutex, 0, 1);
	
	for(i=0; i<N; i++)
	{
		pthread_create(&thread[i], NULL, philosopher, &phil[i]);
	}
	
	for (i = 0; i < N; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	return 0;
}
