#include <iostream>
#include <vector>
#include <Windows.h>
#include "BaseTest.hpp"
#include "GetLocalTime.hpp"
#include "BaseFunction.hpp"

static constexpr ULONGLONG THRESHOLD = 40000;

static bool _isDebugged()
{
	SYSTEMTIME st1 = { 0 };
	SYSTEMTIME st2 = { 0 };
	FILETIME t1 = { 0 };
	FILETIME t2 = { 0 };
	ULARGE_INTEGER u1 = { 0 };
	ULARGE_INTEGER u2 = { 0 };
	ULONGLONG val = 1;
	GetLocalTime(&st1);
	for (size_t i = 0; i < 1000000; i++)
	{
		val *= i;
	}
	GetLocalTime(&st2);
	SystemTimeToFileTime(&st1, &t1);
	SystemTimeToFileTime(&st2, &t2);
	u1.LowPart = t1.dwLowDateTime;
	u1.HighPart = t1.dwHighDateTime;
	u2.LowPart = t2.dwLowDateTime;
	u2.HighPart = t2.dwHighDateTime;

	return ((u2.QuadPart - u1.QuadPart) > THRESHOLD);
}

Timing::GetLocalTimeTest::GetLocalTimeTest()
{
	lf = LogFile("getlocaltime.log", "Timing", "GetLocalTime");
}

void Timing::GetLocalTimeTest::RunTest()
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
			std::cout << "[GetLocalTimeTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}