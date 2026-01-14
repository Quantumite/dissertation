#include "BaseTest.hpp"
#include "BaseFunction.hpp"

void BaseTest(void)
{
#ifdef INTEL
	LogFile lf = LogFile("basetest.log", "Base", "BaseTest");
#else
	LogFile lf = LogFile("basetest_arm.log", "Base", "BaseTest");
#endif
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Start test
	for(size_t i=0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		BaseFunction3(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
		
	}
}
