#include "MemoryEncryption.hpp"
#include "CodeObfuscation.hpp"
#include "SelfDebugging.hpp"

namespace Misc{
    void RunMiscTests()
    {
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

        //Code Obfuscation Test
        CodeObfuscationTest cot = CodeObfuscationTest();
        cot.PreRun();
        cot.RunTest();
        cot.PostRun();

    }
}