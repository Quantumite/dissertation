#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "NtSetDebugFilterState.hpp"
#include "BaseFunction.hpp"

API::NtSetDebugFilterStateTest::NtSetDebugFilterStateTest() {
	lf = LogFile("ntsetdebugfilterstate.log", "API", "NtSetDebugFilterState");
}
void API::NtSetDebugFilterStateTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		pNtSetDebugFilterState NtSetDebugFilterState = (pNtSetDebugFilterState)GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtSetDebugFilterState");
		if (!NtSetDebugFilterState)
		{
			std::cout << "Unable to find NtSetDebugFilterState()" << std::endl;
			exit(1);
		}
		if (!NtSetDebugFilterState(0,0,true))
		{
			std::cout << "[NtSetDebugFilterStateTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}