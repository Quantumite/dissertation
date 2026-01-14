#include <iostream>
#include <vector>
#include <functional>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "CodeChecksum.hpp"
#include "Fletcher.hpp"
#include "BaseFunction.hpp"

//Fletcher-16 checksum of first 50 bytes of FuncToScan value

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

bool Scanning::CodeChecksumTest::PreRun()
{
	//high likelihood to change with each compile, this guarantees
	// we get the right value at the beginning of the test and it
	// would only be changed if something was debugging it during
	// the test.
    const auto pFunc = FuncToScan;
	Fletcher fChecksum = Fletcher<unsigned int (*)()>(pFunc, (size_t)50);
	mChecksum = fChecksum.GetChecksum();
	return true;
}

Scanning::CodeChecksumTest::CodeChecksumTest() {
	lf = LogFile("codechecksum.log", "Scanning", "CodeChecksum");
}
void Scanning::CodeChecksumTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	bool isDebugged = true;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
    const auto pFunc = FuncToScan;

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
	    Fletcher fChecksum = Fletcher<unsigned int (*)()>(pFunc, (size_t)50);
		if (mChecksum != fChecksum.GetChecksum())
		{
			std::cout << "[CodeChecksumTest] Debugger detected. Exiting.\n" << std::endl;
			exit(1);
		}

		BaseFunction3(iDataVector, i);
  
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}

