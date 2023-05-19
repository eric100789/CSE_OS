#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define MAXLEN 4096

using namespace std;

void sigcont(int sig);
void sigquit(int sig);

char str[MAXLEN];
int fd;
void *p;

int main()
{
	if (signal(SIGCONT, sigcont) == SIG_ERR) return 0;

	int pid = fork();
	
	if(pid > 0)
	{
		signal(SIGINT, sigquit);
		fd = open("text.txt", 'r');
		p = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		
		char *ptr = (char *)p;
		size_t cnum = 0;
		printf("When user enter \'\\n\', text.txt will be changed:\n");
		printf("---------Write something---------\n");
		while (~scanf("%[^\n]s", str))
		{
			getchar();
			size_t len = strlen(str);
			str[len++] = '\n';

			cnum += len;
			if (cnum > MAXLEN)
			{
				printf("MEMORY FULL\n");
				break;
			}

			while(ftruncate(fd, cnum) == -1)
			{
				printf("ftruncate ERROR\n");
			}
			memcpy(ptr, str, len);
			ptr += len;

			kill(pid, SIGCONT);
		}

		printf("Your write is finished.\n");
		
		munmap(p, getpagesize());
		close(fd);

		kill(pid, SIGQUIT);

		int s;
		waitpid(pid, &s, 0);
		return 0;
	}
	else if(pid == 0)
	{
		fd = open("text.txt", 'r');

		p = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);
		if (p == (void *)-1)
		{
			printf("MAPPING ERROR\n");
			return 0;;
		}

		close(fd);
		while(true) pause();
	}
	else
	{
		printf("FORK ERROR\n");
		return 0;;
	}
}

void sigcont(int sig)
{
	system("clear");
	printf("---------Something is read---------\n");
	memcpy(str, p, getpagesize());
	printf("READ:\n%s",str);
	printf("---------Write something---------\n");
}
void sigquit(int sig)
{
	printf("\nunmapped, waiting for exit...\n");
	sleep(1);
	munmap(p, getpagesize());
	exit(0);
}
