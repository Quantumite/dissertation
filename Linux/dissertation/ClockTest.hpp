#pragma once
#include "LogFile.hpp"

namespace Timing
{
    class ClockTest
    {
        public:
        ClockTest();

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