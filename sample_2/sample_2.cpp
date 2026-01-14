// sample_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <Wincrypt.h>
#include <vector>
#include <string>
#include <iostream>
#include "..\AntiDebuggingResearch\Timing.hpp"
#include "..\AntiDebuggingResearch\LogFile.hpp"

#define LOOPSIZE 1010

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

int main()
{
    auto lf = LogFile("sample2_windows.log", "Sample", "Sample2");
    AntiDebuggingTimer adt = AntiDebuggingTimer();

    for (size_t i = 0; i < LOOPSIZE; i++)
    {
        adt.AntiDebugging_TimeStart();

        //run sample test
        if (_isDebugged())
        {
            std::cout << "[NtQueryPerformanceCounter] Debugger detected. Exiting.\n" << std::endl;
            return -1;
        }
        
        DWORD temp = 0;
        for (DWORD j = 0; j < (DWORD)100; j++) temp += j;


        //write data
        adt.AntiDebugging_TimeStop();
        lf.Write(adt.PrintResults(lf));
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
