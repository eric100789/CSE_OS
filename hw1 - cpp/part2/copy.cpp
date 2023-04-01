#include "parser.h"

#define FIRST_CMD(index) (exe.cmd[0]->argv[index])
#define REPLY_ERROR(message) do{cout<<message<<endl; return;}while(0)
#define STD_INPUT 0
#define STD_OUTPUT 1

using namespace std;

static void reply_error(string message)
{
	fprintf(stderr, "%s\n", message.c_str());
	exit(EXIT_FAILURE);
	return;
}

void run(execution exe)
{
	int status;
	//cd
	if(FIRST_CMD(0) == "cd")
	{
		chdir(FIRST_CMD(1).c_str());
	}
	// quit
	else if (FIRST_CMD(0) == "exit" || FIRST_CMD(0) == "quit" || FIRST_CMD(0) == "q")
	{
		exit(0);
	}
	
	int pid = fork();
	if(pid != 0)
	{
		// parent
		if(!exe.bg)
			waitpid(pid, &status, 0);
	}
	else
	{
		// child
		exe.oper.pop_back();
		if(exe.oper.size() == 0)
		{
			if(exe.infile != "")
			{
				vector<string> v;
				v.push_back(exe.infile);
				char ** converted = cmd_transform(v);
			
				// pipeline
				int fd = open(exe.cmd[0]->argv[0].c_str(), 'r');
				if(!fd) REPLY_ERROR("File Error");
				close(STDIN_FILENO);
				dup(fd);
				close(fd);
				if(!execvp(converted[0], converted)) REPLY_ERROR("Execution Error");
				
				for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted[i];
			}
			else if(exe.outfile != "")
			{
				char ** converted = cmd_transform(exe.cmd[0]->argv);
			
				// pipeline
				int fd = open(exe.outfile.c_str(), O_WRONLY | O_CREAT, 0644);
				if(!fd) REPLY_ERROR("File Error");
				close(STD_OUTPUT);
				dup(fd);
				close(fd);
				if(!execvp(converted[0], converted)) REPLY_ERROR("Execution Error");
				
				for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted[i];
			}
			else
			{
				char ** converted = cmd_transform(exe.cmd[0]->argv);
				/*int j=0;
				while(1)
				{
					if(converted[j] == NULL) break;
					cout << converted[j++] << endl;
				}*/
				int test = execvp(converted[0], &converted[0]);
				if(!test) REPLY_ERROR("Execution Error");
				for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted[i];
			}
		}
		else if(exe.oper[0] == '|')
		{
			char ** converted1 = cmd_transform(exe.cmd[0]->argv);
			char ** converted2 = cmd_transform(exe.cmd[1]->argv);
			
			// pipeline
			int fd[2];
			pipe(fd);
			
			int pid2 = fork();
			if(pid2 != 0)
			{
				if(exe.infile != "")
				{
					fd[0] = open(exe.cmd[0]->argv[0].c_str(), O_RDONLY);
					exe.cmd[0]->argv[0] = exe.infile;
					converted1 = cmd_transform(exe.cmd[0]->argv);
					dup2(fd[0],STD_INPUT);
				}
				close(fd[0]);
				close(STD_OUTPUT);
				dup(fd[1]);
				close(fd[1]);
				if(!execvp(converted1[0], converted1)) REPLY_ERROR("Execution Error");
			}
			else
			{
				close(fd[1]);
				close(STD_INPUT);
				dup(fd[0]);
				close(fd[0]);
				if(exe.outfile != "")
				{
					fd[0] = open(exe.outfile.c_str(), O_WRONLY | O_CREAT, 0644);
					dup2(fd[0],STD_OUTPUT);
				}
				if(!execvp(converted2[0], converted2)) REPLY_ERROR("Execution Error");
			}
			
			for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted1[i];
			for(int i=0; i<exe.cmd[1]->argv.size(); i++) delete converted2[i];
		}
		else if(exe.oper[0] == '>')
		{
			char ** converted = cmd_transform(exe.cmd[0]->argv);
		
			// pipeline
			int fd = open(exe.cmd[1]->argv[0].c_str(), O_WRONLY | O_CREAT, 0644);
			if(!fd) REPLY_ERROR("File Error");
			close(STD_OUTPUT);
			dup(fd);
			close(fd);
			if(!execvp(converted[0], converted)) REPLY_ERROR("Execution Error");
			
			for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted[i];
		}
		else if(exe.oper[0] == '<')
		{
			char ** converted = cmd_transform(exe.cmd[0]->argv);
		
			// pipeline
			int fd = open(exe.cmd[1]->argv[0].c_str(), O_RDONLY);
			if(!fd) REPLY_ERROR("File Error");
			close(STD_INPUT);
			dup(fd);
			close(fd);
			if(!execvp(converted[0], converted)) REPLY_ERROR("Execution Error");
			
			for(int i=0; i<exe.cmd[0]->argv.size(); i++) delete converted[i];
		}
	}
}

void reset_exe(execution & exe)
{
	for(int i=0 ; i<exe.cmd.size() ; i++)
	{
		exe.cmd[i]->argv.clear();
		delete exe.cmd[i];
	}
	exe.bg = false;
	exe.oper.clear();
}
