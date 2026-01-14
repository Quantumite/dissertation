#pragma once
#include "LogFile.hpp"
#include <array>

namespace Scanning
{
    class EnumProcessTest
    {
        std::array<const char *, 6> BADPROCESSNAMES = {"gdb", "lldb", "kdbg", "valgrind", "strace", "ltrace"};
        public:
            EnumProcessTest();

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
            bool ValidateProcessCheck(void);
            LogFile lf;
    };


}