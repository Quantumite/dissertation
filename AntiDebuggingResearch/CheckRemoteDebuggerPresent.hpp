#pragma once
#include "LogFile.hpp"

namespace API {
	class CheckRemoteDebuggerPresentTest {
	public:
		CheckRemoteDebuggerPresentTest();

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

