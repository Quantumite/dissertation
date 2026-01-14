#pragma once
#include <string>
#include <array>
#include "LogFile.hpp"

typedef union _LARGE_INTEGER {
    struct {
        uint32_t LowPart;
        long HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        uint32_t LowPart;
        long HighPart;
    } u;
    long long QuadPart;
} LARGE_INTEGER;

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
	long lpFrequency = 0L;
	std::string sTestName = "";
	uint32_t aux = 0;
	std::array<int, 4> regs;
};