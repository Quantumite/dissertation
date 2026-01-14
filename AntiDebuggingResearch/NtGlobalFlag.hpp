#pragma once
#include "LogFile.hpp"

namespace API {
	class NtGlobalFlagTest {
	public:
		NtGlobalFlagTest();

		bool PreRun()
		{
			return true;
		}
		void RunTest();
		bool PostRun()
		{
			return true;
		}

		static constexpr DWORD FLAG = 0x10 | 0x20 | 0x40; // FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS;

	private:
		LogFile lf;
	};

}