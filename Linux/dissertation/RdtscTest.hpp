#pragma once
#include "LogFile.hpp"

#ifdef INTEL
#include <x86intrin.h>
#endif


namespace Timing
{
    class RDTSCTest 
    {
        public:
        RDTSCTest();

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