#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class GetSystemTimeTest
	{
	public:
		GetSystemTimeTest();

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

