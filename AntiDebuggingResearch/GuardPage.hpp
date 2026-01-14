#pragma once
#include "LogFile.hpp"

namespace Exception {
	class GuardPageTest {
	public:
		GuardPageTest();

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
