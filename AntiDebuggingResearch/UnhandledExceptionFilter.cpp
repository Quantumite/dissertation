#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "UnhandledExceptionFilter.hpp"
#include "BaseFunction.hpp"

static bool bIsDebugged = true;

static LONG AntiDebugFilter(PEXCEPTION_POINTERS pExceptionPointers)
{
	bIsDebugged = false;
	return EXCEPTION_CONTINUE_EXECUTION;
}

static bool _isDebugged()
{
	LPTOP_LEVEL_EXCEPTION_FILTER Top = SetUnhandledExceptionFilter(AntiDebugFilter);
	RaiseException(EXCEPTION_FLT_DIVIDE_BY_ZERO, 0, 0, nullptr);
	SetUnhandledExceptionFilter(Top);
	return bIsDebugged;
}

Exception::UnhandledExceptionFilterTest::UnhandledExceptionFilterTest() {
	lf = LogFile("unhandledexceptionfilter.log", "Exception", "UnhandledExceptionFilter");
}
void Exception::UnhandledExceptionFilterTest::RunTest()
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
			std::cout << "[UnhandledExceptionFilterTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}