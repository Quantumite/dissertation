#include <iostream>
#include <string>
#include <array>
#include "Timing.hpp"
#include "LogFile.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

static uint32_t cpufreq()
{
	uint32_t freq = 0;
	asm volatile ("mrs %0, cntfrq_el0" : "=r"(freq));
	return freq;
}

void AntiDebuggingTimer::GetTicksPerSecond(void)
{
	//Modifies the member variable, lpFrequency, to hold the Ticks per Second value
	lpFrequency = (long long)cpufreq();
}

void AntiDebuggingTimer::AntiDebugging_TimeStart(void)
{
	//avoids out of order execution by calling ISB first
	asm ("ISB;"
		"MRS %0, CNTVCT_EL0"
			: "=r" (startTime));
}

void AntiDebuggingTimer::AntiDebugging_TimeStop(void)
{
	//avoids out of order execution by calling ISB first
	asm ("ISB;"
		"MRS %0, CNTVCT_EL0"
			: "=r" (endTime));
}

std::string AntiDebuggingTimer::PrintResults(std::string testType, std::string testName)
{
	std::string results = testType+"-"+testName+",";

	if (startTime != 0 && endTime != 0 && endTime > startTime && lpFrequency != 0)
	{
		//Default measurement is microseconds
		uint64_t temp = ((endTime - startTime) * 1000000) / lpFrequency;
		results += std::to_string(temp);
		results += " (microseconds)\n";
	}
	else
	{
		std::cerr << "[ERROR] INVALID VALUES FOR TIMING CLASS." << startTime << "," << endTime << "," << lpFrequency << std::endl;
	}	
	return results;
}

std::string AntiDebuggingTimer::PrintResults(LogFile& lf)
{
	return PrintResults(lf.GetTestType(), lf.GetTestName());
}