#include <iostream>
#include <vector>
#include <Windows.h>
#include <Winternl.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "HeapFlag.hpp"
#include "BaseFunction.hpp"

API::HeapFlagTest::HeapFlagTest() {
	lf = LogFile("heapflag.log", "API", "HeapFlag");
}

void API::HeapFlagTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
	PPEB pebPtr = nullptr;
	PVOID pHeap = nullptr;
	DWORD dwHeapFlag = 0;
	DWORD dwHeapForceFlag = 0;

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		pebPtr = reinterpret_cast<PPEB>(__readgsqword(0x60));
		pHeap = *reinterpret_cast<PVOID*>((char*)pebPtr + 0x30);
		dwHeapFlag = *reinterpret_cast<DWORD*>((char*)pHeap + 0x70);
		dwHeapForceFlag = *reinterpret_cast<DWORD*>((char*)pHeap + 0x74);
		if ((dwHeapFlag & ~HEAP_GROWABLE) != 0 || (dwHeapForceFlag & FORCEFLAG) != 0)
		{
			std::cout << "[HeapFlagTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}






}