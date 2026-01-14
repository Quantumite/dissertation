#pragma once
#include "LogFile.hpp"

namespace Misc
{
    class SelfDebuggingTest
    {
        public:
        SelfDebuggingTest();

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
