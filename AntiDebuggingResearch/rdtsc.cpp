#include <iostream>
#include <vector>
#include <Windows.h>
#include "BaseTest.hpp"
#include "rdtsc.hpp"
#include "BaseFunction.hpp"

static constexpr ULONGLONG THRESHOLD = 12000000;

static bool _isDebugged()
{
	ULONGLONG time1 = 0;
	ULONGLONG time2 = 0;
	ULONGLONG val = 1;
	time1 = __rdtsc();
	for (size_t i = 0; i < 1000000; i++)
	{
		val *= i;
	}
	time2 = __rdtsc();
	return ((time2 - time1) > THRESHOLD);
}

Timing::RdtscTest::RdtscTest()
{
	lf = LogFile("rdtsc.log", "Timing", "GetLocalTime");
}

void Timing::RdtscTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();

		if (_isDebugged())
		{
			std::cout << "[RdtscTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}