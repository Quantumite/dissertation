#pragma once
#include <string>
#include <array>
#include "LogFile.hpp"
#include <Windows.h>

class AntiDebuggingTimer
{
public:
	AntiDebuggingTimer() 
	{
		GetTicksPerSecond();
	};

	void GetTicksPerSecond(void);
	void AntiDebugging_TimeStart(void);
	void AntiDebugging_TimeStop(void);
	std::string PrintResults(std::string testType, std::string testName);
	std::string PrintResults(LogFile& lf);

private:
	uint64_t startTime = 0;
	uint64_t endTime = 0;
	LARGE_INTEGER lpFrequency = { 0 };
	std::string sTestName = "";
	uint32_t aux = 0;
	std::array<int, 4> regs;
};

