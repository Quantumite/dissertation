#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "EventPairHandles.hpp"
#include "BaseFunction.hpp"

API::EventPairHandlesTest::EventPairHandlesTest() {
	lf = LogFile("eventpairhandles.log", "API", "EventPairHandles");
}
void API::EventPairHandlesTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
	PDEBUG_BUFFER buffer = nullptr;
	HMODULE nt = nullptr;

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		nt = GetModuleHandle(L"ntdll.dll");
		if (!nt)
		{
			std::cout << "Unable to get handle to ntdll.dll. Exiting.\n" << std::endl;
			exit(1);
		}

		HEAP_GROWABLE
		
		pRtlCreateQueryDebugBuffer RtlCreateQueryDebugBuffer = (pRtlCreateQueryDebugBuffer)GetProcAddress(nt, "RtlCreateQueryDebugBuffer");
		pRtlQueryProcessDebugInformation RtlQueryProcessDebugInformation = (pRtlQueryProcessDebugInformation)GetProcAddress(nt, "RtlQueryProcessDebugInformation");
		buffer = RtlCreateQueryDebugBuffer(0, FALSE);
		(void)RtlQueryProcessDebugInformation(GetCurrentProcessId(), PDI_HEAPS|PDI_HEAP_BLOCKS, buffer);

		if ((buffer->RemoteSectionBase == (PVOID)0x50000062) || (buffer->EventPairHandle == (PVOID)0x00002b98) ){
			std::cout << "[EventPairHandles] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}