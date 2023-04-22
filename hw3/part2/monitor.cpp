#include "monitor.h"
#include <pthread.h>
#include <semaphore.h>
#include <cstdio>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <signal.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

monitor::monitor()
{
	mutex = PTHREAD_MUTEX_INITIALIZER;
	for(int i=0; i<N; i++)
	{
		s[i] = PTHREAD_COND_INITIALIZER;
		s_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
	}
}

void monitor::take_forks(int i)
{
	srand(time(NULL));
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry.\n", i);
    if(!test(i))
    {
        pthread_mutex_unlock(&mutex);
        pthread_cond_wait(&s[i], &s_mutex[i]);
        sleep(rand()%2+1);
    }
    else
        pthread_mutex_unlock(&mutex);
}

void monitor::put_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = THINKING;
	printf("Philosopher %d puts fork %d and %d down.\n",i,LEFT,i);
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex);
}

void monitor::think(int i)
{
	srand(time(NULL));
	printf("Philosopher %d is thinking.\n",i);
	sleep(rand()%2+1);
}

int monitor::test(int i)
{
    if(state[i] == HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
    {
        state[i] = EATING;
		printf("Philosopher %d takes fork %d and %d up.\n",i,LEFT,i);
		printf("Philosopher %d is eating.\n",i);
        pthread_cond_broadcast(&s[i]);
        pthread_mutex_unlock(&s_mutex[i]);
        return 1;
    }
    return 0;
}
