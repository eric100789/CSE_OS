#include "parser.h"

using namespace std;

void welcome_print(void)
{
	cout << endl;
	printf("█░░░█ █▀▀ █░░ █▀▀ █▀▀█ █▀▄▀█ █▀▀ 　 ▀▀█▀▀ █▀▀█ \n");
	printf("█▄█▄█ █▀▀ █░░ █░░ █░░█ █░▀░█ █▀▀ 　 ░░█░░ █░░█  \n");
	printf("░▀░▀░ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀▀ ▀░░░▀ ▀▀▀ 　 ░░▀░░ ▀▀▀▀\n");
	cout << endl;
	printf("█▀▄▀█ █░░█ 　 █▀▀ █░░█ █▀▀ █░░ █░░\n");
	printf("█░▀░█ █▄▄█ 　 ▀▀█ █▀▀█ █▀▀ █░░ █░░ \n");
	printf("▀░░░▀ ▄▄▄█ 　 ▀▀▀ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀\n");
	cout << endl;
}

void debug_print(execution exe)
{
	cout << "Status: " << endl << (exe.bg ? "Background" : "Non Background") << endl;
	cout << "Command: " << endl << "> ";
	
	for(int i=0; i<exe.cmd.size(); i++)
	{
		for(int j=0; j<exe.cmd[i]->argv.size(); j++)
		{
			cout << exe.cmd[i]->argv[j];
		}
		cout << exe.oper[i];
	}
	cout << endl;
}

execution read_line(void)
{
	cout << ">";
	execution exe;
	
	char c;
	string s = "";
	vector<string> s_vec;
	while(true)
	{
		c = getchar();
		if(c == '&')
		{
			exe.bg = true;
		}
		else if(c=='\n' && s_vec.size()==0 && s=="")
		{
			continue;
		}
		else if(c==' ' && s=="")
		{
			continue;
		}
		else if(c==' ')
		{
			s_vec.push_back(s);
			s = "";
		}
		else if(c=='|' || c=='>' || c=='<')
		{
			command * cmd = new command;
			exe.oper.push_back(c);
			exe.cmd.push_back(cmd);
			if(s != "")
			{
				 s_vec.push_back(s);
				 //s_vec.push_back(NULL);
			}
			for(auto x: s_vec)
			{
				(cmd->argv).push_back(x);
			}
			s = "";
			s_vec.clear();
		}
		else if(c=='\n' || c==EOF)
		{
			command * cmd = new command;
			exe.cmd.push_back(cmd);
			if(s != "")
			{
				 s_vec.push_back(s);
				 //s_vec.push_back(NULL);
			}
			exe.oper.push_back('\0');
			for(auto x: s_vec)
			{
				(cmd->argv).push_back(x);
			}
			s = "";
			s_vec.clear();
			break;
		}
		else
		{
			s = s+c;
		}
	}
	return exe;
}

char ** cmd_transform(vector<string> cmdvec)
{
	char** argv = new char*[cmdvec.size()+1];
	for(int i=0 ; i<cmdvec.size() ; i++)
	{
		argv[i] = new char[cmdvec[i].size()+1];
		strcpy(argv[i], cmdvec[i].c_str());
	}
	argv[cmdvec.size()] = NULL;
	return argv;
}


