#include <iostream>
#include <string>
#include <array>
#include <Windows.h>
#include <intrin.h>
#include "Timing.hpp"
#include "LogFile.hpp"

void AntiDebuggingTimer::GetTicksPerSecond(void)
{
	//Modifies the member variable, lpFrequency, to hold the Ticks per Second value
	(void)QueryPerformanceFrequency(&lpFrequency);
}

void AntiDebuggingTimer::AntiDebugging_TimeStart(void)
{
	//avoids out of order execution by calling cpuid first
	(void)__cpuid(regs.data(), 0);
	startTime = __rdtsc();
}

void AntiDebuggingTimer::AntiDebugging_TimeStop(void)
{
	//guarantees execution of all the previous instructions before this is ran at the end
	endTime = __rdtscp(&aux);
	(void)__cpuid(regs.data(), 0);
}

std::string AntiDebuggingTimer::PrintResults(std::string testType, std::string testName)
{
	std::string results = testType+"-"+testName+",";

	if (startTime != 0 && endTime != 0 && endTime > startTime && lpFrequency.QuadPart != 0)
	{
		//Default measurement is microseconds
		uint64_t temp = ((endTime - startTime) * 1000000) / lpFrequency.QuadPart;
		results += std::to_string(temp);
		results += " (microseconds)\n";
	}
	else
	{
		std::cerr << "[ERROR] INVALID VALUES FOR TIMING CLASS." << startTime << "," << endTime << "," << lpFrequency.QuadPart << std::endl;
	}	
	return results;
}

std::string AntiDebuggingTimer::PrintResults(LogFile& lf)
{
	return PrintResults(lf.GetTestType(), lf.GetTestName());
}