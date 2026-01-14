#pragma once
#include <Windows.h>
#include <iostream>
#include <array>
#include "LogFile.hpp"

static std::array<std::wstring, 11> bad_parent_name_array = { L"dbg", L"windbg", L"windbgx", L"ollydbg", L"debug", L"monitor", L"watch", L"x96dbg", L"x64dbg", L"x64dbg", L"enghost" };

namespace Scanning
{
	class ParentProcessTest
	{
	public:
		ParentProcessTest();

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
		DWORD GetParentProcessId(void);
		std::wstring GetParentProcessName();
		bool ValidateParentProcessCheck(void);
		LogFile lf;
	};

}






