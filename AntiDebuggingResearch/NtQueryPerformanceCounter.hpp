#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class NtQueryPerformanceCounterTest
	{
	public:
		NtQueryPerformanceCounterTest();

		bool PreRun()
		{
			return true;
		}
		void RunTest();
		bool PostRun()
		{
			return true;
		}

	private:
		LogFile lf;
	};

}


