#pragma once
#include "LogFile.hpp"

namespace Scanning
{
    class IsTracerPidZeroTest {
        public:
        IsTracerPidZeroTest();

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
