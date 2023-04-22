#include <pthread.h>
#include <semaphore.h>
#include <cstdio>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include "monitor.h"

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

monitor mon;

void *philosopher(void *data)
{
    int i = *((int*) data);
    while(1)
    {
        mon.think(i);
        mon.take_forks(i);
        mon.put_forks(i);
    }
    pthread_exit(NULL);
}

int main()
{
	int i;
	pthread_t thread[N];
	int arg[N];
	
	for(i=0; i<N; i++)
	{
		arg[i] = i;
		pthread_create(&thread[i], NULL, philosopher, &arg[i]);
	}
	
	while(1)
	{
		sleep(10);
	}

	return 0;
}
