/*This code is from https://linuxsecurity.com/features/anti-debugging-for-noobs-part-1*/
#include "BaseTest.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool IsTracerPidNonzero(void)
{
	std::string line;
	std::ifstream file("/proc/self/status");
	while(std::getline(file, line))
	{
		std::istringstream _stream(line);
		std::string tag, value;
		_stream >> tag >> value;
		if(tag == "TracerPid:" && value != "0") return true;
	}
	return false;
}

void AntiDebugger_IsTracerPidNonzero(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	std::string functionName = std::string("IsTracerPidNonzero");
	size_t tmp = 0;

	//Measure
	ResearchTimer r(functionName+" (Total)");
	for (size_t i = 0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);
		if (IsTracerPidNonzero())
		{
			std::cout << "Debugger detected. Exiting.\n" << std::endl;
			exit(1);
		}

		iDataVector.push_back(i);
		for (size_t j = 0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp * j) % 1024;
			iDataVector.at(i) = tmp;
		}
		r2.stop();
	}
}
