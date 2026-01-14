#include "BaseTest.hpp"
#include <unistd.h>

typedef uint32_t(*myfunc)(long n);

uint32_t fib(long n)
{
	long base = 0;
	long i = 0;
	long j = 1;
	long tmp = 0;
	while (base++ < n)
	{
		tmp = i + j;
		i = j;
		j = tmp;
	}
	return tmp;
}

uint32_t doNothing(long n)
{
	return 0;
}

void ValidateCodeObfuscationTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	std::string functionName = std::string("CodeObfuscationTest");

	//Timing
	ResearchTimer r(functionName+" (Total)");

	ptrdiff_t doNothingToFib = (ptrdiff_t)((uintptr_t)fib - (uintptr_t)doNothing);
	uint32_t(*runme)(long) = (uint32_t(*)(long))((uintptr_t)doNothing + doNothingToFib);

	for (size_t i = 0; i < BUFSIZE; i+=4)
	{
		//Loop 1
		ResearchTimer r2(functionName);
		iDataVector.push_back(i);
		for (size_t j = 0; j < 1024; j+=2)
		{
			tmp = iDataVector.at(i);
			tmp = (tmp * (j/2) * 2) % 1024;
			iDataVector.at(i) = tmp;
			(*runme)(32);
			tmp = iDataVector.at(i);
			tmp = (tmp * ((j+1) / 2) * 2) % 1024;
			iDataVector.at(i) = tmp;
		}
		r2.stop();

		//Loop 2
		r2.start(functionName);
		iDataVector.push_back(i+1);
		for (size_t j = 0; j < 1024; j+=4)
		{
			tmp = iDataVector.at(i+1);
			tmp = (tmp * j*2)/2 % 1024;
			iDataVector.at(i+1) = tmp;
			(*runme)(17);
			tmp = iDataVector.at(i + 1);
			tmp = (tmp * (j+1) * 2) / 2 % 1024;
			iDataVector.at(i + 1) = tmp;
			(*runme)(9);
			tmp = iDataVector.at(i + 1);
			tmp = (tmp * (j+2) * 2) / 2 % 1024;
			iDataVector.at(i + 1) = tmp;
			(*runme)(99);
			tmp = iDataVector.at(i + 1);
			tmp = (tmp * (j+3) * 2) / 2 % 1024;
			iDataVector.at(i + 1) = tmp;
		}
		r2.stop();

		//Loop 3
		r2.start(functionName);
		iDataVector.push_back(i+2);
		for (size_t j = 0; j < 1024; j+=6)
		{
			tmp = iDataVector.at(i+2);
			tmp = ((tmp * j+1) - tmp) % 1024;
			iDataVector.at(i+2) = tmp;
			(*runme)(51);
			tmp = iDataVector.at(i + 2);
			tmp = ((tmp * ((j+1) + 1)) - tmp) % 1024;
			iDataVector.at(i + 2) = tmp;
			(*runme)('a');
			tmp = iDataVector.at(i + 2);
			tmp = ((tmp * ((j+2) + 1)) - tmp) % 1024;
			iDataVector.at(i + 2) = tmp;
			(*runme)(3);
			tmp = iDataVector.at(i + 2);
			tmp = ((tmp * ((j+3) + 1)) - tmp) % 1024;
			iDataVector.at(i + 2) = tmp;
			(*runme)(8);
			tmp = iDataVector.at(i + 2);
			tmp = ((tmp * ((j+4) + 1)) - tmp) % 1024;
			iDataVector.at(i + 2) = tmp;
			(*runme)(7);
			tmp = iDataVector.at(i + 2);
			tmp = ((tmp * ((j+5) + 1)) - tmp) % 1024;
			iDataVector.at(i + 2) = tmp;
		}
		r2.stop();

		// Loop 4
		r2.start(functionName);
		iDataVector.push_back(i+3);
		for (size_t j = 1024; j < 2048; j++)
		{
			tmp = iDataVector.at(i+3);
			tmp = ((tmp * ((j-1024)-1)) + tmp) % 1024;
			iDataVector.at(i+3) = tmp;
			write(99, nullptr, 0);
		}
		r2.stop();
	}
}
