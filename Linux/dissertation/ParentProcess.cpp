#include "BaseTest.hpp"
#include <unistd.h>
#include <array>
#include <fstream>
#include <string>
#include "ParentProcess.hpp"
#include "BaseFunction.hpp"

bool Scanning::ParentProcessTest::CheckForBadParentNames(void)
{
	pid_t ppid = getppid();
	std::string proc_parent_cmdline = "/proc/"+std::to_string(ppid)+"/cmdline";
	std::ifstream file(proc_parent_cmdline);
	std::string line;
	std::getline(file, line);

	for(auto& bad_name : Scanning::ParentProcessTest::BADPARENTNAMES)
	{
		if(line.find(bad_name) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

Scanning::ParentProcessTest::ParentProcessTest()
{
	lf = LogFile("parentprocess.log", "Scanning", "ParentProcess");
}

void Scanning::ParentProcessTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp=0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if(CheckForBadParentNames())
		{
			std::cout << "Debugger detected! Quitting." << std::endl;
			exit(1);
		}
		
		BaseFunction3(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
