#include "BaseTest.hpp"
#include "SelfDebugging.hpp"
#include "BaseFunction.hpp"

Misc::SelfDebuggingTest::SelfDebuggingTest()
{
	lf = LogFile("selfdebugging.log", "Misc", "SelfDebugging");
}

bool Misc::SelfDebuggingTest::CreateSelfDebuggingProcess(PROCESS_INFORMATION *pi)
{
	std::wstring commandLine;
	WCHAR* commandLine2 = nullptr;

	//Create commandline string
	commandLine += L"SelfDebuggingChild.exe ";
	commandLine += std::to_wstring(GetCurrentProcessId());

	//Create startupinfo struct
	STARTUPINFO startupInfo = { 0 };
	startupInfo.cb = sizeof(STARTUPINFO);

	//Create processinformation struct
	PROCESS_INFORMATION processInformation = { 0 };

	return CreateProcess(
		L"SelfDebuggingChild.exe",
		&commandLine[0],
		NULL,
		NULL,
		false,
		//CREATE_NO_WINDOW,
		0,
		NULL,
		NULL,
		&startupInfo,
		pi);
}

void Misc::SelfDebuggingTest::RunTest(void)
{
	
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
	PROCESS_INFORMATION pi = { 0 };

	//Timing
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (!CreateSelfDebuggingProcess(&pi))
		{
			std::cout << "Unable to start self-debugging child process." << std::endl;
			return;
		}
		
		BaseFunction5(iDataVector, i);

		if (pi.hProcess != 0 && !TerminateProcess(pi.hProcess, 0))
		{
			std::cout << "Unable to terminate child process, self-debugger. GLE=" << std::hex << GetLastError() << std::endl;
		}
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}