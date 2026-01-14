#pragma once
#include "LogFile.hpp"

namespace Timing
{
	class RdtscTest
	{
	public:
		RdtscTest();

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


