#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "CheckRemoteDebuggerPresent.hpp"
#include "BaseFunction.hpp"

API::CheckRemoteDebuggerPresentTest::CheckRemoteDebuggerPresentTest() {
	lf = LogFile("checkremotedebuggerpresent.log", "API", "CheckRemoteDebuggerPresent");
}
void API::CheckRemoteDebuggerPresentTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		BOOL bIsDebuggerPresent = false;
#pragma warning (suppress : 4312)
		(void)CheckRemoteDebuggerPresent((HANDLE)GetCurrentProcessId(), &bIsDebuggerPresent);
		if (bIsDebuggerPresent)
		{
			std::cout << "[CheckRemoteDebuggerPresent] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}