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
	cout << "Status: " << (exe.bg ? "Background" : "Non Background") << endl;
	cout << "Infile: " << (exe.infile != "" ? exe.infile : "Non File") << endl;
	cout << "Outfile: " << (exe.outfile != "" ? exe.outfile : "Non File") << endl;
	cout << "Command: " << endl << "$ ";
	
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
	cout << "$";
	execution exe;
	exe.infile = "";
	exe.outfile = "";
	exe.bg = false;
	
	
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
		else if(c=='|')
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
		else if(c=='<')
		{
			if(s_vec.size() != 0)
			{
				string ss = s;
				s = "";
				for(int k=0; k<s_vec.size(); k++) s = s+s_vec[k];
				s = s+ss;
			}
			exe.infile = s;
			s = "";
			s_vec.clear();
		}
		else if(c == '>')
		{
			string ss;
			cin >> ss;
			string sss = "";
			for(int k=0; k<ss.size() ; k++)
			{
				if(ss[k] == '&')
				{
					exe.bg = true;
					exe.outfile = sss;
					command * cmd = new command;
			exe.cmd.push_back(cmd);
			if(s != "")
			{
				 s_vec.push_back(s);
			}
			exe.oper.push_back('\0');
			for(auto x: s_vec)
			{
				(cmd->argv).push_back(x);
			}
			s = "";
			s_vec.clear();
					goto STOP;
				}
				else
				{
					sss = sss+ss[k];
				}
			}
			exe.outfile = ss;
			command * cmd = new command;
			exe.cmd.push_back(cmd);
			if(s != "")
			{
				 s_vec.push_back(s);
			}
			exe.oper.push_back('\0');
			for(auto x: s_vec)
			{
				(cmd->argv).push_back(x);
			}
			s = "";
			s_vec.clear();
			char cc;
			while(true)
			{
				cc=getchar();
				if(cc=='\n' || cc==EOF) goto STOP;
				else if (cc=='&')
				{
					exe.bg = true;
					goto STOP;
				}
			}
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
	STOP:
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


