#pragma once
#include "LogFile.hpp"

namespace API {
	class IsDebuggerPresentTest {
	public:
		IsDebuggerPresentTest();

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
