#pragma once
#include "LogFile.hpp"

namespace Scanning
{
	class CodeChecksumTest
	{
	public:
		CodeChecksumTest();

		bool PreRun();
		void RunTest();
		bool PostRun()
		{
			return true;
		}

	private:
		LogFile lf;
		WORD mChecksum = 0;
	};

}
