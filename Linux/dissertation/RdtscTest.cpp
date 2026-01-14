#include "BaseTest.hpp"
#include <ctime>
#include <unistd.h>
#include "RdtscTest.hpp"
#include "BaseFunction.hpp"

Timing::RDTSCTest::RDTSCTest()
{
	lf = LogFile("rdtsctest.log", "Timing", "RDTSC");
}

void Timing::RDTSCTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	uint64_t start;
	uint64_t end;
	uint64_t clock_diff = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i<LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
#ifdef INTEL
		start = __rdtsc();
#elif AARCH64
		asm ("ISB;"
		"MRS %0, CNTVCT_EL0"
			: "=r" (start));
#else
#endif

		BaseFunction3(iDataVector, i);

#ifdef INTEL
		end = __rdtsc();
#elif AARCH64
		asm ("ISB;"
		"MRS %0, CNTVCT_EL0"
			: "=r" (end));
#else
#endif
		auto time_measure = (end - start);
		if(time_measure > 20000000)
		{
			std::cout << "Function took too long to run, likely being debugged.\n" << std::endl;
			exit(1);
		}
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
