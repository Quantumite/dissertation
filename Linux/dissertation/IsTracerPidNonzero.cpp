/*This code is from https://linuxsecurity.com/features/anti-debugging-for-noobs-part-1*/
#include "BaseTest.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "IsTracerPidNonzero.hpp"
#include "Timing.hpp"
#include "BaseFunction.hpp"


static bool IsTracerPidNonzero(void)
{
	std::string line;
	std::ifstream file("/proc/self/status");
	for(std::string line; std::getline(file, line);)
	{
		std::istringstream _stream(line);
		std::string tag, value;
		_stream >> tag >> value;
		if(tag == "TracerPid:" && value != "0") return true;
	}
	return false;
}

Scanning::IsTracerPidZeroTest::IsTracerPidZeroTest()
{
	lf = LogFile("istracerpidzero.log", "Scanning", "IsTracerPidZero");
}

void Scanning::IsTracerPidZeroTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (IsTracerPidNonzero())
		{
			std::cout << "Debugger detected. Exiting.\n" << std::endl;
			exit(1);
		}

		BaseFunction3(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
