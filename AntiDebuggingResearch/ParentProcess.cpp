#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <vector>
#include "ParentProcess.hpp"
#include "BaseTest.hpp"
#include "BaseFunction.hpp"

Scanning::ParentProcessTest::ParentProcessTest()
{
	lf = LogFile("parentprocess.log", "Scanning", "ParentProcess");
}

DWORD Scanning::ParentProcessTest::GetParentProcessId(void)
{
	DWORD pid = GetCurrentProcessId();
	DWORD ppid = 0;
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe = { 0 };
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessList, &pe))
	{
		do {
			if (pe.th32ProcessID == pid)
			{
				ppid =  pe.th32ParentProcessID;
			}
		} while (Process32Next(hProcessList, &pe));
	}
	CloseHandle(hProcessList);

	return ppid;
}

std::wstring Scanning::ParentProcessTest::GetParentProcessName()
{
	
	DWORD ppid = GetParentProcessId();
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	std::wstring pParentProcessName;
	PROCESSENTRY32 pe = { 0 };
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessList, &pe))
	{
		do {
			if (pe.th32ProcessID == ppid)
			{
				pParentProcessName = std::wstring(pe.szExeFile, pe.szExeFile + MAX_PATH);
			}
		} while (Process32Next(hProcessList, &pe));
	}
	CloseHandle(hProcessList);

	return pParentProcessName;
}

bool Scanning::ParentProcessTest::ValidateParentProcessCheck(void)
{
	std::wstring parentProcessString = GetParentProcessName();

	for (auto& c : parentProcessString)
	{
		c = towlower(c);
	}
	
	for (const auto& bad : bad_parent_name_array)
	{
		if (parentProcessString.find(bad) != std::wstring::npos)
		{
			return true;
		}
	}

	return false;
}

void Scanning::ParentProcessTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Timing
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (ValidateParentProcessCheck())
		{
			std::cout << "[ParentProcessTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}
		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}