#pragma once
#include <array>
#include "LogFile.hpp"

namespace Scanning
{

    class ParentProcessTest
    {
        std::array<const char *, 6> BADPARENTNAMES = {"gdb", "lldb", "kdbg", "valgrind", "strace", "ltrace"};

        public:
        ParentProcessTest();

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
        bool CheckForBadParentNames(void);
        LogFile lf;
    };
}