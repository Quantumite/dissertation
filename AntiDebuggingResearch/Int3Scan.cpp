#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "Int3Scan.hpp"
#include "BaseFunction.hpp"

static unsigned int FuncToScan()
{
	int a = 1;
	float b = 79;
	int sum = 100;
	for (size_t i = 0; i < 10; i++)
	{
		sum += (int)i * (int)i;
	}

	float c = b * sum;
	return (unsigned int)c >> 7;
}

static bool _isDebugged(PVOID data, size_t length)
{
	char* localData = (char*)data;
	for (size_t i=0; i < length; i++)
	{
		if (localData[i] == '\xcc') return true;
	}
	return false;
}

Scanning::Int3ScanTest::Int3ScanTest() {
	lf = LogFile("int3scan.log", "Scanning", "Int3Scan");
}
void Scanning::Int3ScanTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	BOOL isDebugged = true;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (_isDebugged(FuncToScan, (size_t)50))
		{
			std::cout << "[Int3ScanTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}

