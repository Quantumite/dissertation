#include "BaseTest.hpp"
#include <ctime>
#include <unistd.h>
#include "ClockTest.hpp"
#include "BaseFunction.hpp"

Timing::ClockTest::ClockTest()
{
	lf = LogFile("clocktest.log", "Timing", "Clock");
}

void Timing::ClockTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	clock_t start;
	clock_t end;
	clock_t clock_diff = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i<LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		start = clock();

		BaseFunction3(iDataVector,i);

		end = clock();
		auto time_measure = (end - start);
		if(time_measure > 10000)
		{
			std::cout << "Function took too long to run, likely being debugged.\n" << std::endl;
			exit(1);
		}
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
