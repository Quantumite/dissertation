#include "BaseTest.hpp"
#include <ctime>
#include <unistd.h>
#include "ClockGetTimeTest.hpp"
#include "BaseFunction.hpp"

#define SEC_TO_NANO 1000000000 //1 billion, 10^9

Timing::ClockGetTimeTest::ClockGetTimeTest()
{
	lf = LogFile("clockgettimetest.log", "Timing", "Clock_GetTime");
}

void Timing::ClockGetTimeTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	struct timespec start;
	struct timespec end;
	uint64_t clock_diff = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i<LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		clock_gettime(CLOCK_REALTIME,&start);

		BaseFunction3(iDataVector, i);

		clock_gettime(CLOCK_REALTIME,&end);
		auto time_measure = ((end.tv_sec*SEC_TO_NANO + end.tv_nsec) - (start.tv_sec*SEC_TO_NANO + start.tv_nsec));
		if(time_measure > 10000000)
		{
			std::cout << "Function took too long to run, likely being debugged.\n" << std::endl;
			exit(1);
		}
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
