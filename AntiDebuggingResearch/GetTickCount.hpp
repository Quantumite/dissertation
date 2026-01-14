#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class GetTickCountTest
	{
	public:
		GetTickCountTest();

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


