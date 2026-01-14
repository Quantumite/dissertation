#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class TimeGetTimeTest
	{
	public:
		TimeGetTimeTest();

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


