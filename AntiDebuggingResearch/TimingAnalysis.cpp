#include "BaseTest.hpp"

void ValidateTimingAnalysisTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();
	DWORD dwTimingAnalysisStart = 0;

	//Timing
	timeBeginPeriod(100);
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		dwTimingAnalysisStart = timeGetTime();
		iDataVector.push_back(i);
		for (size_t j = 0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp * j) % 1024;
			iDataVector.at(i) = tmp;
		}
		//If execution takes longer than 500ms (0.5 seconds) then its likely being debugged
		if (timeGetTime() - dwTimingAnalysisStart > 500)
		{
			std::cout << "Function took too long to run, likely being debugged. Exiting." << std::endl;
			return;
		}
		adt.AntiDebugging_TimeStop();
	}
}