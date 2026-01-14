#include "BaseTest.hpp"
#include <ctime>
#include <unistd.h>

void ValidateTimingAnalysis(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	std::string functionName = std::string("TimingAnalysisTest");
	time_t start;
	time_t end;
	uint64_t clock_diff = 0;
	double time_measure = 0.0;

	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i<BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);
		time(&start);
		iDataVector.push_back(i);
		for(size_t j=0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp*j) % 1024;
			iDataVector.at(i) = tmp;
		}

		time(&end);
		time_measure = (end - start);
		std::cout << time_measure << std::endl;
		if(time_measure > 1)
		{
			std::cout << "Function took too long to run, likely being debugged.\n" << std::endl;
			exit(1);
		}
		r2.stop();
	}
}
