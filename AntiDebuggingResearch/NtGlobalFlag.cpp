#include <iostream>
#include <vector>
#include <Windows.h>
#include <Winternl.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "NtGlobalFlag.hpp"
#include "BaseFunction.hpp"

API::NtGlobalFlagTest::NtGlobalFlagTest() {
	lf = LogFile("ntglobalflag.log", "API", "NtGlobalFlag");
}

void API::NtGlobalFlagTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
	PPEB pebPtr = nullptr;
	DWORD dwCurrentFlagValue = -1;

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		pebPtr = reinterpret_cast<PPEB>(__readgsqword(0x60));
		dwCurrentFlagValue = *reinterpret_cast<DWORD*>((char*)pebPtr + 0xbc);
		if ((dwCurrentFlagValue & FLAG) != 0)
		{
			std::cout << "[NtGlobalFlagTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}


	
	
	

}