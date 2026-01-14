#pragma once
#include "LogFile.hpp"
#include <cstdint>

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
		uint16_t mChecksum = 0;
	};

}