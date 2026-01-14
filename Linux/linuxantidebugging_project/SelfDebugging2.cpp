#include "BaseTest.hpp"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

void ValidateSelfDebuggingTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	std::string functionName = std::string("SelfDebuggingTest");

	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);
		if(ptrace(PTRACE_TRACEME, 0) < 0)
		{
			std::cout << "oh no, being debugged!" << std::endl;
			exit(1);
		}

		//No debugger yet...
		if(ptrace(PTRACE_TRACEME, 0) != -1)
		{
			std::cout << "something went wrong..." << std::endl;
			exit(1);

		}

		//We are tracing ourselves now, do stuff
		iDataVector.push_back(i);
		for(size_t j=0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp*j) % 1024;
			iDataVector.at(i) = tmp;
		}

		ptrace(PTRACE_DETACH, 0);
		r2.stop();

		
	}
}
