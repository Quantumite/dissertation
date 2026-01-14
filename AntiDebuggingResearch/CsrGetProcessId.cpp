#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "CsrGetProcessId.hpp"
#include "BaseFunction.hpp"

API::CsrGetProcessIdTest::CsrGetProcessIdTest() {
	lf = LogFile("csrgetprocessid.log", "API", "CsrGetProcessId");
}
void API::CsrGetProcessIdTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		HMODULE nt = GetModuleHandle(L"ntdll.dll");
		if (!nt)
		{
			std::cout << "Unable to get handle to ntdll.dll. Exiting.\n" << std::endl;
			exit(1);
		}
		_CsrGetProcessId CsrGetProcessId = (_CsrGetProcessId)GetProcAddress(nt, "CsrGetProcessId");
		HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CsrGetProcessId());
		if (proc)
		{
			std::cout << "[CsrGetProcessId] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}