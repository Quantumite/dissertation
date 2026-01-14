#include "RunTimingTests.hpp"
#include "GetLocalTime.hpp"
#include "GetSystemTime.hpp"
#include "TimeGetTime.hpp"
#include "GetTickCount.hpp"
#include "rdtsc.hpp"
#include "NtQueryPerformanceCounter.hpp"

void Timing::RunTimingTests()
{
	//GetLocalTime Tests
	GetLocalTimeTest gltt = GetLocalTimeTest();
	gltt.PreRun();
	gltt.RunTest();
	gltt.PostRun();

	//GetSystemTime Tests
	GetSystemTimeTest gstt = GetSystemTimeTest();
	gstt.PreRun();
	gstt.RunTest();
	gstt.PostRun();

	//timeGetTime Tests
	TimeGetTimeTest tgtt = TimeGetTimeTest();
	tgtt.PreRun();
	tgtt.RunTest();
	tgtt.PostRun();	

	//NtQueryPerformanceCounter Tests
	NtQueryPerformanceCounterTest nqpct = NtQueryPerformanceCounterTest();
	nqpct.PreRun();
	nqpct.RunTest();
	nqpct.PostRun();

	//GetTickCount Tests
	GetTickCountTest gtct = GetTickCountTest();
	gtct.PreRun();
	gtct.RunTest();
	gtct.PostRun();

	//RDTSC tests
	RdtscTest rt = RdtscTest();
	rt.PreRun();
	rt.RunTest();
	rt.PostRun();
}