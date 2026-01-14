#include "Int3Scan.hpp"
#include "CodeChecksum.hpp"
#include "ParentProcess.hpp"
#include "EnumProcess.hpp"
#include "IsTracerPidNonzero.hpp"

namespace Scanning {
    void RunScanningTests()
    {
        //IsTracerPidZero Test
        IsTracerPidZeroTest itpzt = IsTracerPidZeroTest();
        itpzt.PreRun();
        itpzt.RunTest();
        itpzt.PostRun();

        //int3 scan Test
        Int3ScanTest i3st = Int3ScanTest();
        i3st.PreRun();
        i3st.RunTest();
        i3st.PostRun();

        //checksum test
        CodeChecksumTest cct = CodeChecksumTest();
        cct.PreRun();
        cct.RunTest();
        cct.PostRun();

        //parent process test
        ParentProcessTest ppt = ParentProcessTest();
        ppt.PreRun();
        ppt.RunTest();
        ppt.PostRun();

        //Process enum test
        EnumProcessTest ept = EnumProcessTest();
        ept.PreRun();
        ept.RunTest();
        ept.PostRun();

    }
}