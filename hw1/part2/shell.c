#include "shell.h"

#define GET_BUFFER_SIZE 32
#define PAR_BUFFER_SIZE 16
#define CMD_BUFFER_SIZE 8
#define STD_INPUT 0
#define STD_OUTPUT 1

static void exception(char * message)
{
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
	return;
}

void free_cmd(command * cmd)
{
	for(int i=0 ; i<999999 ; i++)
	{
		if(cmd[i].par == -1) break;
			
		for(int j=0; j<cmd[i].par ; j++)
		{
			free(cmd[i].argv[j]);
		}
	}
	free(cmd);
}

command* read_line(void)
{
	//Command_numbers = 0;
	int get_size = GET_BUFFER_SIZE;
	int par_size = PAR_BUFFER_SIZE;
	int cmd_size = CMD_BUFFER_SIZE;
	
	int get_now = 0;
	int par_now = 0;
	int cmd_now = 0;
	
	char *cbuf = malloc(sizeof(char) * get_size);
	char **argvbuf = malloc(sizeof(char*) * par_size);
	command *cmdbuf = malloc(sizeof(command) * cmd_size);
	
	if(!cbuf || !argvbuf || !cmdbuf ) exception("Allocation Error");
	
	char c;
	while(1)
	{
		c = getchar();
		if(c == ' ' && get_now == 0) continue;
		if(c == ' ' || c=='\n' || c==EOF)
		{
			cbuf[get_now] = '\0';
			get_now = 0;
			get_size = GET_BUFFER_SIZE;
			if(par_now >= par_size)
			{
				par_size += PAR_BUFFER_SIZE;
				argvbuf = realloc(argvbuf, par_size);
				if(!argvbuf) exception("Allocation Error");
			}
			argvbuf[par_now] = cbuf;
			++par_now;
			cbuf = malloc(sizeof(char) * GET_BUFFER_SIZE);
			if(!cbuf) exception("Allocation Error");
		}
		if(c == '|' || c=='\n' || c==EOF)
		{
			/*
			if(c == '|')
			{
				if(cmd_now >= cmd_size)
				{
					cmd_size += PAR_BUFFER_SIZE;
					cmdbuf = realloc(cmdbuf, cmd_size);
					if(!cmdbuf) exception("Allocation Error");
				}
				
				cmdbuf[cmd_now].argv = NULL;
				cmdbuf[cmd_now].par = -2;
				++cmd_now;
			}*/

			if(cmd_now >= cmd_size)
			{
				cmd_size += PAR_BUFFER_SIZE;
				cmdbuf = realloc(cmdbuf, cmd_size);
				if(!cmdbuf) exception("Allocation Error");
			}
			
			cmdbuf[cmd_now].argv = argvbuf;
			cmdbuf[cmd_now].par = par_now;
			par_now = 0;
			par_size = PAR_BUFFER_SIZE;
			++cmd_now;
			if(c == '|')
			{
				argvbuf = malloc(sizeof(char*) * PAR_BUFFER_SIZE);
				if(!argvbuf) exception("Allocation Error");
			}
		}
		if (c=='\n' || c==EOF)
		{
			if(cmd_now >= cmd_size)
			{
				cmd_size += PAR_BUFFER_SIZE;
				cmdbuf = realloc(cmdbuf, cmd_size);
				if(!cmdbuf) exception("Allocation Error");
			}
			++cmd_now;
			cmdbuf[cmd_now].par = -1;
			cmdbuf[cmd_now].argv = NULL;
			return cmdbuf;
		} 
		if(c!='\n' && c!=EOF && c!='|' && c!=' ')
		{
			cbuf[get_now] = c;
			++get_now;
			if(get_now >= get_size)
			{
				get_size += GET_BUFFER_SIZE;
				cbuf = realloc(cbuf, get_size);
				if(!cbuf) exception("Allocation Error");
			}
		}
	}
	return NULL;
	
}

void run (command * cmd)
{
	int fd[2];
	if(pipe(fd) == -1)
		exception("Pipeline Error");
		
	int *pid = malloc(sizeof(int) * CMD_BUFFER_SIZE);
	int num = 0;
	int size = CMD_BUFFER_SIZE;
	
	do
	{
		if(num >= size)
		{
			size += CMD_BUFFER_SIZE;
			pid = realloc(pid, size);
		}
		
		if(cmd[num].par == -1) break;
		pid[num] = fork();
		
		if(pid[num] < 0)
			exception("Fork Error");
			
		if(pid[num] == 0)
		{
			dup2(fd[1], STD_OUTPUT);
			close(fd[0]);
			close(fd[1]);
			execvp(cmd[num].argv[0], &cmd[num].argv[0]);
		}
		else if(pid[num] == 1)
		{
			dup2(fd[1], STD_OUTPUT);
		}
		++num;
		
	}while(pid[num-1] == 1);
	
	close(fd[0]);
	close(fd[1]);
	
	for(int i=0 ; i<num-1; i++)
	{
		waitpid(pid[i], NULL, 0);
	}
	
	
}


