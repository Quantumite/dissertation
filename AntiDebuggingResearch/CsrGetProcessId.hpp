#pragma once
#pragma once
#include "LogFile.hpp"

typedef DWORD(*_CsrGetProcessId)();

namespace API {
	class CsrGetProcessIdTest {
	public:
		CsrGetProcessIdTest();

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
