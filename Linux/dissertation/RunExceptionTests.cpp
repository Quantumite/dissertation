#include "int3.hpp"
#include "TrapFlag.hpp"

namespace Exception{
    void RunExceptionTests()
    {
        //Int3 exception test
        Int3Test i3t = Int3Test();
        i3t.PreRun();
        i3t.RunTest();
        i3t.PostRun();

#ifdef INTEL
        //trap flag exception test
        TrapFlagTest tft = TrapFlagTest();
        tft.PreRun();
        tft.RunTest();
        tft.PostRun();
#endif
    }
}