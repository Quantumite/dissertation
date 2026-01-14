#include <iostream>

void PrintUsage(void)
{
	std::cout << "Anti-Debugging Research Tool\n";
	std::cout << "Created by Austin Norby (quantumite)\n";
	std::cout << "\n";
	std::cout << "This binary accepts a single paramter for the type of test to run:\n\n";
	
	std::cout << "\tBase Test: b\n";
	std::cout << "\t\tThe Base Test runs the code without any anti-debugging measures enabled. Used for baseline measurement.\n\n";
	
	std::cout << "\tWindows API Test: a\n";
	std::cout << "\t\tThe Windows API Test runs the IsDebuggerPresent() function at the beginning of each iteration of the Base Test to measure timing effects.\n\n"; 
	
	std::cout << "\tCode Obfuscation Test: c\n";
	std::cout << "\t\tRun the base test that has code obfuscation operations applied to it. Including function pointer arithmatic, unnecessary instructions, and loop unrolling.\n\n";

	std::cout << "\tDebug Registers Test: d\n";
	std::cout << "\t\tCheck the debug registers to see if any are non-zero; non-zero debug registers likely means a debugger has been used on the process.\n\n";

	std::cout << "\tMemory Encryption Test: m\n";
	std::cout << "\t\tDecrypts memory before performing base test operations on the memory and re-encrypts it after use.\n\n";

	std::cout << "\tValidate Parent Process Test: p\n";
	std::cout << "\t\tResolve the parent process name and check if it contains known invalid options such as: 'debug', 'dbg', 'windbg', ollydbg', etc.\n\n";

	std::cout << "\tSelf-debugging Test: s\n";
	std::cout << "\t\tCreates a child process that debugs this process to prevent another debugger from attaching to it. Uses SelfDebuggingChild.exe as child process.\n\n";

	std::cout << "\tTiming Analysis Test: t\n";
	std::cout << "\t\tMeasures the time it takes work to be completed and if that work takes longer than 0.5 seconds, its likely a debugger has been attached.\n\n";
	std::cout << std::endl;
}