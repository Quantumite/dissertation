// SelfDebuggingChild.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>
#include <debugapi.h>

int main(int argc, char** argv)
{
    DEBUG_EVENT dbgEvent;
    std::string strParentProcessId(argv[1]);
    std::cout <<  "Parent Process ID: " << strParentProcessId << std::endl;
    DWORD dwParentProcessId = static_cast<DWORD>(stoi(strParentProcessId));

    //Start debugging parent process here
    //Attach to parent process as self-debugger
    if (!DebugActiveProcess(dwParentProcessId))
    {
        std::cout << "Unable to attach to parent process as self-debugger. GLE=" << std::hex << GetLastError() << std::endl;
        return 1;
    }

    //Disable killing of debugged process (parent process)
    if (!DebugSetProcessKillOnExit(false))
    {
        std::cout << "Unable to modify DebugSetProcessKillOnExit() for self-debugger. GLE=" << std::hex << GetLastError() << std::endl;
        return 1;
    }

    while (true)
    {
        if (!WaitForDebugEvent(&dbgEvent, INFINITE))
        {
            std::cout << "Unable to attach to parent process (self-debug) after 10 seconds. GLE=" << std::hex << GetLastError() << std::endl;
            return 1;
        }
        /*else
        {
            std::cout << "dbgEvent.dwDebugEventCode=" << dbgEvent.dwDebugEventCode << "\n";
            std::cout << "dbgEvent.dwProcessId=" << dbgEvent.dwProcessId << std::endl;
        }*/

        if (!ContinueDebugEvent(dbgEvent.dwProcessId, dbgEvent.dwThreadId, DBG_CONTINUE))
        {
            std::cout << "Unable to continue debug event. GLE=" << std::hex << GetLastError() << std::endl;
            return 1;
        }
    }
}