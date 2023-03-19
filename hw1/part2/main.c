#include <stdio.h>
#include "shell.h"

void debug(command * cmd)
{
	for(int i=0 ; i<99999 ; i++)
	{
		if(cmd[i].par == -1) return;
		else if(cmd[i].par == -2){}
		for(int j=0; j<cmd[i].par ; j++)
		{
			printf("%s ", cmd[i].argv[j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{	
	
	/* read command */
	printf(">");
	command * cmd = read_line();
	//execvp(cmd[1].argv[0], &cmd[1].argv[0]);
	run(cmd);
	free_cmd(cmd);

	return EXIT_SUCCESS;
}
