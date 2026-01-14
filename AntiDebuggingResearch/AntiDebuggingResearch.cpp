// AntiDebuggingResearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "PrintUsage.hpp"
#include "RunAPITests.hpp"
#include "RunExceptionTests.hpp"
#include "RunScanningTests.hpp"
#include "BaseTest.hpp"
#include "RunTimingTests.hpp"
#include "RunMiscTests.hpp"

/* References for this code:
  - https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timegettime
  - https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
  - https://en.cppreference.com/w/
  - https://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
  - https://anti-debug.checkpoint.com/techniques/process-memory.html
  - https://learn.microsoft.com/en-us/windows/win32/seccng/typical-cng-programming
  - https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgeneratesymmetrickey
  - https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgetproperty
  - https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptencrypt
  - https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptopenalgorithmprovider
  - https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createprocessa
*/

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        PrintUsage();
        exit(0);
    }
    else if (argc == 2)
    {
        char option = argv[1][0];
        switch (option)
        {
        
        case 'a':
            //Windows API Tests
            API::RunAPITests();
            break;
        case 'b':
            //BaseTest
            BaseTest();
            break;
        case 'e':
            //Windows Exception Tests
            Exception::RunExceptionTests();
            break;
        case 'm':
            //misc test
            //ValidateMemoryEncryptionTest();
            Misc::RunMiscTests();
            break;
        case 's':
            //self debugging test
            Scanning::RunScanningTests();
            break;
        case 't':
            //validate timing analysis
            Timing::RunTimingTests();
            break;
        default:
            std::cout << "Invalid option.\n\n";
            PrintUsage();
            exit(1);
        }
    }
    else 
    {
        std::cout << "Invalid commandline.\n\n" << std::endl;
        PrintUsage();
        exit(1);
    }

    return 0;
}