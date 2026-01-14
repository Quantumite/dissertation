#pragma once
#include "LogFile.hpp"

typedef NTSTATUS(*pNtSetDebugFilterState)(INT, INT, BOOL);

namespace API {
	class NtSetDebugFilterStateTest {
	public:
		NtSetDebugFilterStateTest();

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

