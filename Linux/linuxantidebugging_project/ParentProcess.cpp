#include "BaseTest.hpp"
#include <unistd.h>
#include <array>
#include <fstream>
#include <string>

static constexpr std::array<const char *, 6> BADPARENTNAMES = {"gdb", "lldb", "kdbg", "valgrind", "strace", "ltrace"};

bool CheckForBadParentNames(void)
{
	pid_t ppid = getppid();
	std::string proc_parent_cmdline = "/proc/"+to_string(ppid)+"/cmdline";

	std::string line;
	std::ifstream file(proc_parent_cmdline);
	std::getline(file,line);

	for(auto& bad_name : BADPARENTNAMES)
	{
		if(line.find(bad_name) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

void RunParentProcessCheck(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp=0;
	std::string functionName = std::string("ParentProcessTest");

	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);
		if(!CheckForBadParentNames())
		{
			iDataVector.push_back(i);
			for(size_t j=0; j < 1024; j++)
			{
				tmp = iDataVector.at(i);
				tmp = (tmp*j) % 1024;
				iDataVector.at(i) = tmp;
			}

		}
		else
		{
			std::cout << "Debugger detected! Quitting." << std::endl;
			exit(1);
		}
		r2.stop();
	}
}
