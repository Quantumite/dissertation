#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "Int2d.hpp"
#include "BaseFunction.hpp"

extern "C" void __Int2d();

static bool bIsDebugged = true;

static LONG AntiDebugFilter(PEXCEPTION_POINTERS pExceptionPointers)
{
	bIsDebugged = false;
	return EXCEPTION_CONTINUE_EXECUTION;
}

static bool _isDebugged()
{
	__try
	{
		__Int2d();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		bIsDebugged = false;
	}

	return bIsDebugged;
}

Exception::Int2dTest::Int2dTest() {
	lf = LogFile("int2d.log", "Exception", "Int2d");
}
void Exception::Int2dTest::RunTest()
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
			std::cout << "[Int2dTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
