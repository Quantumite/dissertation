#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "EnumProcess.hpp"
#include "BaseTest.hpp"
#include "BaseFunction.hpp"

Scanning::EnumProcessTest::EnumProcessTest()
{
	lf = LogFile("enumprocess.log", "Scanning", "EnumProcess");
}

bool Scanning::EnumProcessTest::ValidateProcessCheck(void)
{
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe = { 0 };
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessList, &pe))
	{
		std::wstring processName(pe.szExeFile, pe.szExeFile + MAX_PATH);
		std::transform(processName.begin(), processName.end(), processName.begin(), [](wchar_t c)
			{
				return std::tolower(c);
			});
		do {
			for (const auto& bad : Scanning::bad_parent_name_array)
			{
				if (processName.find(bad) != std::wstring::npos)
				{
					return true;
				}
			}

		} while (Process32Next(hProcessList, &pe));
	}
	CloseHandle(hProcessList);
	return false;
}

void Scanning::EnumProcessTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Timing
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (ValidateProcessCheck())
		{
			std::cout << "[EnumProcessTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}
		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}