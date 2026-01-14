#include <iostream>
#include <vector>
#include <Windows.h>
#include "BaseTest.hpp"
#include "NtQueryPerformanceCounter.hpp"
#include "BaseFunction.hpp"

static constexpr ULONGLONG THRESHOLD = 50000;

typedef NTSTATUS(*pNtQueryPerformanceCounter)(PLARGE_INTEGER pc, PLARGE_INTEGER pf);

static bool _isDebugged(pNtQueryPerformanceCounter func)
{
	LARGE_INTEGER liTime1 = { 0 };
	LARGE_INTEGER liTime2 = { 0 };
	ULONGLONG val = 1;
	func(&liTime1, nullptr);
	for (size_t i = 0; i < 1000000; i++)
	{
		val *= i;
	}
	func(&liTime2, nullptr);
	return ((liTime2.QuadPart - liTime1.QuadPart) > THRESHOLD);
}

Timing::NtQueryPerformanceCounterTest::NtQueryPerformanceCounterTest()
{
	lf = LogFile("ntqueryperformancecounter.log", "Timing", "NtQueryPerformanceCounter");
}

void Timing::NtQueryPerformanceCounterTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

#pragma warning( suppress : 6387)
	pNtQueryPerformanceCounter NtQueryPerformanceCounter = (pNtQueryPerformanceCounter)GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtQueryPerformanceCounter");
	if (!NtQueryPerformanceCounter)
	{
		std::cerr << "Unable to resolve NtQueryPerformanceCounter()." << std::endl;
		exit(1);
	}

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();

		if (_isDebugged(NtQueryPerformanceCounter))
		{
			std::cout << "[NtQueryPerformanceCounter] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}