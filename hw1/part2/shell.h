#ifndef SHELL_H
#define SHELL_H

#include "parser.h"

static void reply_error(string message);

void run(execution exe);

void reset_exe(execution & exe);

#endif
