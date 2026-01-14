#include <iostream>
#include <vector>
#include <Windows.h>
#include <intrin.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "TrapFlag.hpp"
#include "BaseFunction.hpp"

static bool bIsDebugged = true;

static LONG AntiDebugFilter(PEXCEPTION_POINTERS pExceptionPointers)
{
	bIsDebugged = false;
	if (EXCEPTION_SINGLE_STEP == pExceptionPointers->ExceptionRecord->ExceptionCode)
	{
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	
	return EXCEPTION_CONTINUE_SEARCH;
}

Exception::TrapFlagTest::TrapFlagTest() {
	lf = LogFile("trapflag.log", "Exception", "TrapFlag");
}
void Exception::TrapFlagTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		HANDLE Top = AddVectoredExceptionHandler(1, AntiDebugFilter);
		uintptr_t eflags = __readeflags();
		__writeeflags(eflags | 0x100); //0x100 is the Trap Flag bit
		__nop();
				
		if (bIsDebugged)
		{
			std::cout << "[TrapFlagTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
		bIsDebugged = true;
		RemoveVectoredExceptionHandler(Top);
	}
}