#pragma once
#pragma once
#include "LogFile.hpp"

namespace API {
	class HeapFlagTest {
	public:
		HeapFlagTest();

		bool PreRun()
		{
			return true;
		}
		void RunTest();
		bool PostRun()
		{
			return true;
		}

		// HEAP_GROWABLE | HEAP_TAIL_CHECKING_ENABLED | HEAP_FREE_CHECKING_ENABLED | HEAP_VALIDATE_PARAMETERS_ENABLED
		static constexpr DWORD FLAG = 0x2 | 0x20 | 0x40 | 0x40000000; 

		static constexpr DWORD FORCEFLAG = 0x20 | 0x40 | 0x40000000;

	private:
		LogFile lf;
	};

}