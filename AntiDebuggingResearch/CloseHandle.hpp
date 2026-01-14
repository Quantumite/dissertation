#pragma once
#include "LogFile.hpp"

namespace Exception {
	class CloseHandleTest {
	public:
		CloseHandleTest();

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
