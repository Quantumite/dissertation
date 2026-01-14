#pragma once
#include "LogFile.hpp"

namespace Exception {
	class UnhandledExceptionFilterTest {
	public:
		UnhandledExceptionFilterTest();

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
