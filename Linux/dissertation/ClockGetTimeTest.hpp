#pragma once
#include "LogFile.hpp"

namespace Timing
{
    class ClockGetTimeTest
    {
        public:
        ClockGetTimeTest();

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