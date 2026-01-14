#pragma once
#include "LogFile.hpp"

namespace Exception {
	class Int2dTest {
	public:
		Int2dTest();

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

