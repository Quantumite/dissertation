#pragma once
#include "LogFile.hpp"

namespace API {
	class OutputDebugStringTest {
	public:
		OutputDebugStringTest();

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
