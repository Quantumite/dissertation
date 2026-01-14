#pragma once
#include "LogFile.hpp"

namespace Timing
{
    class TimeTest
    {
        public:
        TimeTest();

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