#include <iostream>
#include <vector>
#include <Windows.h>
#include "BaseTest.hpp"
#include "GetTickCount.hpp"
#include "BaseFunction.hpp"

static constexpr ULONGLONG THRESHOLD = 16;

static bool _isDebugged()
{
	DWORD dwTime1 = 0;
	DWORD dwTime2 = 0;
	ULONGLONG val = 1;
	dwTime1 = GetTickCount();
	for (size_t i = 0; i < 1000000; i++)
	{
		val *= i;
	}
	dwTime2 = GetTickCount();
	return ((dwTime2 - dwTime1) > THRESHOLD);
}

Timing::GetTickCountTest::GetTickCountTest()
{
	lf = LogFile("gettickcount.log", "Timing", "GetTickCount");
}

void Timing::GetTickCountTest::RunTest()
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
			std::cout << "[GetTickCountTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}