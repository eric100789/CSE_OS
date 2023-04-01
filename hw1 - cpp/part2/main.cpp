#include <iostream>
#include "parser.h"
#include "shell.h"

using namespace std;

int main(void)
{
	welcome_print();
	while(true)
	{
		execution exe = read_line();
		//debug_print(exe);
		run(exe);
		reset_exe(exe);
	}


	return 0;
}
