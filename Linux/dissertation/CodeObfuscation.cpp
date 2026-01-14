#include "BaseTest.hpp"
#include "CodeObfuscation.hpp"
#include <unistd.h>
#include "BaseFunction.hpp"

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

Misc::CodeObfuscationTest::CodeObfuscationTest()
{
	lf = LogFile("codeobfuscation.log", "Misc", "CodeObfuscation");
}

void Misc::CodeObfuscationTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;

	//Timing


	AntiDebuggingTimer adt = AntiDebuggingTimer();

	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		ptrdiff_t doNothingToFib = (ptrdiff_t)((uintptr_t)fib - (uintptr_t)doNothing);
		uint32_t(*runme)(long) = (uint32_t(*)(long))((uintptr_t)doNothing + doNothingToFib);
		//Loop 1
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
			write(99, nullptr, 0);
		}

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}
