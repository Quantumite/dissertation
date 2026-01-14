#pragma once
#include "LogFile.hpp"

namespace Misc
{
	class MemoryEncryptionTest
	{
	public:
		MemoryEncryptionTest();

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

