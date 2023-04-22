#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <pthread.h>
#include <semaphore.h>
#include <cstdio>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

class monitor
{
	public:
	monitor();
	void think(int i);
	void take_forks(int i);
	void put_forks(int i);
	int test(int i);
	
		
	private:
	int state[N];
	pthread_mutex_t mutex;
	pthread_mutex_t s_mutex[N];
	pthread_cond_t s[N];
};

#endif
