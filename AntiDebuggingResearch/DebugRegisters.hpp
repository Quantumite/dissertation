#pragma once
#include "LogFile.hpp"

namespace API {
	class DebugRegistersTest {
	public:
		DebugRegistersTest();

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
