#include <iostream>
#include <vector>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "TrapFlag.hpp"
#include <signal.h>
#include "BaseFunction.hpp"

static bool bIsDebugged = true;

static void sig_handler(int sig_num)
{
    if(sig_num == SIGTRAP)
    {
        bIsDebugged = false;
    }
}

Exception::TrapFlagTest::TrapFlagTest() {
	lf = LogFile("trapflag.log", "Exception", "TrapFlag");
}
void Exception::TrapFlagTest::RunTest()
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
#ifdef INTEL
        __asm__ ("SUBQ $8, %RSP\n\t"
                "pushfq\n\t"
                "ORq $0x100, (%RSP)\n\t"
                "POPFq\n\t"
                "NOP\n\t"
                "ADDQ $8, %RSP\n\t"
        );
#elif AARCH64

#else
#endif
				
		if (bIsDebugged)
		{
			std::cout << "[TrapFlagTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

#ifdef INTEL
        __asm__ ("SUBQ $8, %RSP\n\t"
                "pushfq\n\t"
                "ANDq $0xFFFFFFFFFFFFFEFF, (%RSP)\n\t"
                "POPFq\n\t"
                "NOP\n\t"
                "ADDQ $8, %RSP\n\t"
                );
#elif AARCH64

#else
#endif

		BaseFunction3(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
		bIsDebugged = true;
	}
}