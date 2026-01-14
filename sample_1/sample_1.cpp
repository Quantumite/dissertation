// sample_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../AntiDebuggingResearch/Timing.hpp"
#include "../AntiDebuggingResearch/LogFile.hpp"

#define LOOPSIZE 1010

int main()
{
    auto lf = LogFile("sample1_windows.log", "Sample", "Sample1");
    AntiDebuggingTimer adt = AntiDebuggingTimer();

    for (size_t i = 0; i < LOOPSIZE; i++)
    {
        adt.AntiDebugging_TimeStart();

        //run sample test
        DWORD temp = 0;
        for (DWORD j = 0; j < (DWORD)-1; j++) temp += j;
        

        //write data
        adt.AntiDebugging_TimeStop();
        lf.Write(adt.PrintResults(lf));
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
