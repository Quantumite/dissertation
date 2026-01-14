#include <iostream>
#include <vector>
#include <Windows.h>
#include "BaseTest.hpp"
#include "TimeGetTime.hpp"
#include "BaseFunction.hpp"

static constexpr ULONGLONG THRESHOLD = 5;

static bool _isDebugged()
{
	DWORD dwTime1 = 0;
	DWORD dwTime2 = 0;
	ULONGLONG val = 1;
	dwTime1 = timeGetTime();
	for (size_t i = 0; i < 1000000; i++)
	{
		val *= i;
	}
	dwTime2 = timeGetTime();
	return ((dwTime2 - dwTime1) > THRESHOLD);
}

Timing::TimeGetTimeTest::TimeGetTimeTest()
{
	lf = LogFile("timegetime.log", "Timing", "TimeGetTime");
}

void Timing::TimeGetTimeTest::RunTest()
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
			std::cout << "[TimeGetTimeTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}