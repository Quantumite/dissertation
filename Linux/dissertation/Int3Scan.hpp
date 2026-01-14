#pragma once
#include "LogFile.hpp"

namespace Scanning
{
	class Int3ScanTest
	{
	public:
		Int3ScanTest();

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