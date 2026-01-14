#pragma once

#pragma once
#include "LogFile.hpp"

namespace Misc
{
	class CodeObfuscationTest
	{
	public:
		CodeObfuscationTest();

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


