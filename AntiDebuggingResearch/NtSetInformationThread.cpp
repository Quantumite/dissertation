#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "NtSetInformationThread.hpp"
#include "BaseFunction.hpp"

API::NtSetInformationThreadTest::NtSetInformationThreadTest() {
	lf = LogFile("ntsetinformationthread.log", "API", "NtSetInformationThread");
}

void API::NtSetInformationThreadTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
#pragma warning (suppress : 4302 4311)
		HANDLE hCurrentThread = OpenThread(THREAD_ALL_ACCESS, false, (DWORD)GetCurrentThread());
		pNtSetInformationThread NtSetInformationThread = (pNtSetInformationThread)GetProcAddress(LoadLibrary(L"ntdll.dll"), "NtSetInformationThread");
		NTSTATUS status = NtSetInformationThread(hCurrentThread, ThreadHideFromDebugger, nullptr, 0);

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}