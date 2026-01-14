#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "IsDebuggerPresent.hpp"
#include "BaseFunction.hpp"

API::IsDebuggerPresentTest::IsDebuggerPresentTest() {
	lf = LogFile("isdebuggerpresent.log", "API", "IsDebuggerPresent");
}
void API::IsDebuggerPresentTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (IsDebuggerPresent())
		{
			std::cout << "[IsDebuggerPresentTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}