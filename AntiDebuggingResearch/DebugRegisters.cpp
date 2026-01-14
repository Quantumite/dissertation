//Credit given to https://anti-debug.checkpoint.com/techniques/process-memory.html

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include "BaseTest.hpp"
#include "DebugRegisters.hpp"
#include "BaseFunction.hpp"

static bool CheckDebugRegisters(void)
{
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (!GetThreadContext(GetCurrentThread(), &ctx))
        return false;

    return ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3;
}

API::DebugRegistersTest::DebugRegistersTest() {
	lf = LogFile("debugregisters.log", "API", "DebugRegisters");
}

void API::DebugRegistersTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		//Measure
		adt.AntiDebugging_TimeStart();
		if (CheckDebugRegisters())
		{
			std::cout << "[DebugRegisterTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}