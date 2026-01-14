#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "GuardPage.hpp"
#include "BaseFunction.hpp"

static bool _isDebugged()
{
	DWORD oldPageProtection = 0;
	PVOID pMemory = VirtualAlloc(nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pMemory)
	{
		std::cout << "Unable to allocate page of memory." << std::endl;
		exit(1);
	}

	*(UCHAR*)pMemory = 0xc3;

	if (!VirtualProtect(pMemory, 0x1000, PAGE_EXECUTE_READWRITE | PAGE_GUARD, &oldPageProtection))
	{
		std::cout << "Unable to change page protections on newly allocated memory." << std::endl;
		exit(1);
	}

	__try
	{
		((void(*)())pMemory)();
	}
	__except (GetExceptionCode() == STATUS_GUARD_PAGE_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		VirtualFree(pMemory, 0, MEM_RELEASE);
		return false;
	}

	VirtualFree(pMemory, 0, MEM_RELEASE);
	return true;
}

Exception::GuardPageTest::GuardPageTest() {
	lf = LogFile("guardpage.log", "Exception", "GuardPage");
}
void Exception::GuardPageTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	BOOL isDebugged = true;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (_isDebugged())
		{
			std::cout << "[GuardPageTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}