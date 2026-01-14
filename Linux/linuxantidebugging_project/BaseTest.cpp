#include "BaseTest.hpp"

void BaseTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	std::string functionName = std::string("BaseTest");

	//Start test
	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);
		iDataVector.push_back(i);
		for(size_t j=0; j < 1024; j++)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp*j) % 1024;
			iDataVector.at(i) = tmp;
		}
		r2.stop();
		
	}
}
