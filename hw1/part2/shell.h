#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RL_BUFFER_SIZE 64

typedef struct _command
{
	char ** argv;
	int par;
}command;

static void exception(char * message);

void free_cmd(command * cmd);

command* read_line(void);

void run (command * cmd);

#endif
