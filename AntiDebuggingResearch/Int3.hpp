#pragma once
#include "LogFile.hpp"

namespace Exception {
	class Int3Test {
	public:
		Int3Test();

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
