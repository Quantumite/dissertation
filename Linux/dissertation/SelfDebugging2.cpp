#include "BaseTest.hpp"
#include "SelfDebugging.hpp"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "BaseFunction.hpp"

Misc::SelfDebuggingTest::SelfDebuggingTest()
{
	lf = LogFile("selfdebugging.log", "Misc", "SelfDebugging");
}

void Misc::SelfDebuggingTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		pid_t child_pid = fork();
		if(child_pid == 0)
		{
			//child process
#ifdef INTEL
			system("./self_debugging_child");
#elif AARCH64

			system("./self_debugging_child_arm");
#else
#endif
		}
		else 
		{
			//We are tracing ourselves now, do stuff
			BaseFunction3(iDataVector, i);
		}

		if(kill(child_pid, SIGTERM) == -1)
		{
			std::cout << "Error occurred while killing child process." << std::endl;
			exit(0);
		}

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
