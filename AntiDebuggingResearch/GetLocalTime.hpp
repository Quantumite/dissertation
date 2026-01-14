#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class GetLocalTimeTest
	{
	public:
		GetLocalTimeTest();

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

