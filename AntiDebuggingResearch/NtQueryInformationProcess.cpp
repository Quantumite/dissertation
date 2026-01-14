#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "NtQueryInformationProcess.hpp"
#include "BaseFunction.hpp"

API::NtQueryInformationProcessTest::NtQueryInformationProcessTest() {
	lf = LogFile("ntqueryinformationprocess.log", "API", "NtQueryInformationProcess");
}
void API::NtQueryInformationProcessTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	
	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		DWORD_PTR dwPortNumber = 0;
		ULONG dwReturnLength = 0;
		pNtQueryInformationProcess NtQueryInformationProcess = (pNtQueryInformationProcess)GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtQueryInformationProcess");
		NTSTATUS status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, &dwPortNumber, sizeof(DWORD_PTR), &dwReturnLength);
		if (status)
		{
			std::cout << "Error calling NtQueryInformationProcess()" << std::endl;
			exit(1);
		}
		if (dwPortNumber != 0)
		{
			std::cout << "[NtQueryInformationProcessTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}