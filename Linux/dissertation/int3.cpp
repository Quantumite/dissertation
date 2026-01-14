#include <iostream>
#include <vector>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "int3.hpp"
#include <signal.h>
#include "BaseFunction.hpp"

static bool bIsDebugged = true;

static bool _isDebugged()
{
#ifdef INTEL
    __asm__ ("int3\n\t");
#elif AARCH64
	//__asm__(".inst 0xd4200000");
	//__asm__("BRK #0xF000");
	raise(SIGTRAP);
#else
#endif
    return bIsDebugged;
}

static void sig_handler(int sig_num)
{
    if(sig_num == SIGTRAP)
    {
        bIsDebugged = false;
    }
}

Exception::Int3Test::Int3Test() {
	lf = LogFile("int3.log", "Exception", "Int3");
}
void Exception::Int3Test::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

    //Initialize signal handler
    signal(SIGTRAP, sig_handler);

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (_isDebugged())
		{
			std::cout << "[Int3Test] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction3(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
		bIsDebugged = true;
	}
}