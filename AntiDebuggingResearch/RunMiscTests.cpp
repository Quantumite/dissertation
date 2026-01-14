#include "CodeObfuscation.hpp"
#include "MemoryEncryption.hpp"
#include "SelfDebugging.hpp"

namespace Misc
{
	void RunMiscTests()
	{
		//Run codeobfuscation tests
		CodeObfuscationTest cot = CodeObfuscationTest();
		cot.PreRun();
		cot.RunTest();
		cot.PostRun();

		//Memory Encryption Test
		MemoryEncryptionTest met = MemoryEncryptionTest();
		met.PreRun();
		met.RunTest();
		met.PostRun();

		//Self-debugging Test
		SelfDebuggingTest sdt = SelfDebuggingTest();
		sdt.PreRun();
		sdt.RunTest();
		sdt.PostRun();
	}
	
}