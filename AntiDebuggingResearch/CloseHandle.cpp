#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "CloseHandle.hpp"
#include "BaseFunction.hpp"

static bool _isDebugged()
{
	__try {
		CloseHandle((HANDLE)0xabcdabcdabcdabcd);
	}
	__except (EXCEPTION_INVALID_HANDLE == GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		return true;
	}

	return false;
}

Exception::CloseHandleTest::CloseHandleTest() {
	lf = LogFile("closehandle.log", "Exception", "CloseHandle");
}
void Exception::CloseHandleTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (_isDebugged())
		{
			std::cout << "[CloseHandle] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}