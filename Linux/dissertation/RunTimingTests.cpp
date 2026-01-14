#include "TimingAnalysis.hpp"
#include "ClockTest.hpp"
#include "ClockGetTimeTest.hpp"
#include "RdtscTest.hpp"

namespace Timing {
    void RunTimingTests()
    {
        //time() Test
        TimeTest tt = TimeTest();
        tt.PreRun();
        tt.RunTest();
        tt.PostRun();

        //clock() Test
        ClockTest ct = ClockTest();
        ct.PreRun();
        ct.RunTest();
        ct.PostRun();

        //clock_gettime Test
        ClockGetTimeTest cgtt = ClockGetTimeTest();
        cgtt.PreRun();
        cgtt.RunTest();
        cgtt.PostRun();

        //RDTSC Test
        RDTSCTest rt = RDTSCTest();
        rt.PreRun();
        rt.RunTest();
        rt.PostRun();
    }
}