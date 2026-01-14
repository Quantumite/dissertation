#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "OutputDebugString.hpp"
#include "BaseFunction.hpp"

API::OutputDebugStringTest::OutputDebugStringTest() {
	lf = LogFile("outputdebugstring.log", "API", "OutputDebugString");
}
void API::OutputDebugStringTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		SetLastError(0);
		OutputDebugStringA("What is the meaning of life?");
		if (GetLastError() != 0)
		{
			std::cout << "[OutputDebugStringTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}