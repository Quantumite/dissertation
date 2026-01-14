#include <vector>
#include "BaseTest.hpp"
#include "LogFile.hpp"
#include "BaseFunction.hpp"

void BaseTest(void)
{
	LogFile lf = LogFile("BaseTest.log", "Base", "BaseTest");
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Timing
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();

		BaseFunction5(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
	
}