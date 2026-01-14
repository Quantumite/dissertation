#pragma once
#include "LogFile.hpp"

namespace Exception {
	class TrapFlagTest {
	public:
		TrapFlagTest();

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

