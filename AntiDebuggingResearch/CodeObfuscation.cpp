#include "BaseTest.hpp"
#include "CodeObfuscation.hpp"

typedef DWORD(*myfunc)(long n);
extern "C" ULONGLONG __fastcall _funcptr(myfunc func1, myfunc func2);

Misc::CodeObfuscationTest::CodeObfuscationTest()
{
	lf = LogFile("codeobfuscation.log", "Misc", "CodeObfuscation");
}

static DWORD fib(long n)
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

static DWORD doNothing(long n)
{
	return 0;
}

void Misc::CodeObfuscationTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();



	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		DWORD(*runme)(long) = (DWORD(*)(long))(_funcptr(doNothing, fib));

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

#pragma warning( suppress : 6387 )
			WriteFile(NULL, NULL, 6, (DWORD*)(&tmp), NULL);
		}

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));	
		
	}
}