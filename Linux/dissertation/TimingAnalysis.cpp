#include "BaseTest.hpp"
#include <ctime>
#include <unistd.h>
#include "TimingAnalysis.hpp"
#include "BaseFunction.hpp"

Timing::TimeTest::TimeTest()
{
	lf = LogFile("timetest.log", "Timing", "Time");
}

void Timing::TimeTest::RunTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	time_t start;
	time_t end;
	uint64_t clock_diff = 0;
	double time_measure = 0.0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for(size_t i=0; i<LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		time(&start);

		BaseFunction3(iDataVector, i);

		time(&end);
		time_measure = (end - start);
		if(time_measure > 2)
		{
			std::cout << "Function took too long to run, likely being debugged.\n" << std::endl;
			exit(1);
		}
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
