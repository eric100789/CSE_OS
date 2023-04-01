#ifndef PARSER_H
#define PARSER_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct _command
{
	vector<string> argv;
} command;

typedef struct _execution
{
	vector<command*> cmd;
	vector<char> oper;
	bool bg;
	string outfile;
	string infile;
} execution;

void welcome_print(void);

void debug_print(execution exe);

execution read_line(void);

char ** cmd_transform(vector<string> cmdvec);

#endif
