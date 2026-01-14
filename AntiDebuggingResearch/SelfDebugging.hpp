#pragma once
#include "BaseTest.hpp"
#include "LogFile.hpp"

namespace Misc
{
	class SelfDebuggingTest
	{
	public:
		SelfDebuggingTest();

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
		bool CreateSelfDebuggingProcess(PROCESS_INFORMATION* pi);
		LogFile lf;
	};

}


