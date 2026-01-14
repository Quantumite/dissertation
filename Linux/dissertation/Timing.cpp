#include <iostream>
#include <string>
#include <array>
#include "Timing.hpp"
#include "LogFile.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <cpuid.h>
#include <x86intrin.h>

static long long cpufreq()
{
    uint32_t cpuFreq = 0;

    // CPU frequency is stored in /proc/cpuinfo in lines beginning with "cpu MHz"
    std::ifstream ifs("/proc/cpuinfo");
    if(ifs.is_open())
    {	
	    std::string line;
	    int results[10];
    
	    while(ifs.good())
	    {
			size_t pos = -1;
	        getline(ifs, line);
			pos = line.find("MHz");
			if( pos == std::string::npos)
			{
				continue;
			}

			size_t pos2 = -1;
			pos2 = line.find(":");
			std::string strCpuFreq(line.substr(pos2+1));

	        // Match found - extract frequency
	        cpuFreq = atoll(strCpuFreq.data());
			cpuFreq *= 1000000; //convert MHz to Hz
	        break;
	    }
    }
    
    ifs.close();
    return cpuFreq;
}

void AntiDebuggingTimer::GetTicksPerSecond(void)
{
	//Modifies the member variable, lpFrequency, to hold the Ticks per Second value
	lpFrequency = cpufreq();
}

void AntiDebuggingTimer::AntiDebugging_TimeStart(void)
{
	//avoids out of order execution by calling cpuid first
	__asm__ __volatile__ ("cpuid\n\t");
	startTime = __rdtsc();
}

void AntiDebuggingTimer::AntiDebugging_TimeStop(void)
{
	//guarantees execution of all the previous instructions before this is ran at the end
	endTime = __rdtscp(&aux);
	__asm__ __volatile__ ("cpuid\n\t");
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