#include <stdio.h>
#include "mm.h"

int main()
{
	printf("Welcome to test area\n");
	printf("0:Exit 1:Malloc 2:Realloc 3:Calloc\n>> ");
	while(1)
	{
		char c = getchar();
		if(c=='0') break;
		else if(c=='1')
		{
			int* tmp = (int*)mymalloc(sizeof(int));
			printf("%p is the memory we malloced.\n", tmp);
			myfree(tmp);
		}
		else if(c=='2')
		{
			int* tmp = (int*)mymalloc(sizeof(int));
			printf("%p is the memory of int we malloced.\n", tmp);
			char* tmp2 = (char*)myrealloc(tmp, sizeof(char));
			printf("%p is the new memory of char we realloced.\n", tmp2);
			myfree(tmp2);
		}
		else if(c=='3')
		{
			int* tmp = (int*)mycalloc(1,sizeof(int));
			printf("%p is the memory we calloced.\n", tmp);
			myfree(tmp);
		}
		else
		{
			printf(">> ");
		}
	}
	
	
	return 0;
}
