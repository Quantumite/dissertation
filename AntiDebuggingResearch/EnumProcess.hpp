#pragma once
#include "LogFile.hpp"
#include <array>

namespace Scanning
{
	static std::array<std::wstring, 11> bad_parent_name_array = { L"dbg", L"windbg", L"windbgx", L"ollydbg", L"debug", L"monitor", L"watch", L"x96dbg", L"x64dbg", L"x64dbg", L"enghost" };

	class EnumProcessTest
	{
	public:
		EnumProcessTest();

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
		bool ValidateProcessCheck(void);
		LogFile lf;
	};

}
