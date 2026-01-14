#include <iostream>

using namespace std;


void PrintUsage(void)

{

	cout << "Anti-Debugging Research Tool\n";
	cout << "Created by Austin Norby (quantumite)\n\n";
	cout << "This binary accepts a single paramter for the type of test to run:\n\n";

	

	cout << "\tBase Test: b\n";
	cout << "\t\tThe Base Test runs the code without any anti-debugging measures enabled. Used for baseline measurement.\n\n";

	
	cout << "\tIsTracerPidNonzero: a\n";
	cout << "\t\tThe IsTracerPidNonzero test finds the line in the /proc/self/status file that has the TracerPid value. This test is comparable to Windows' IsDebuggerPresent().\n\n";


	cout << "\tCode Obfuscation Test: c\n";
	cout << "\t\tRun the base test that has code obfuscation operations applied to it. Including function pointer arithmatic, unnecessary instructions, and loop unrolling.\n\n";



	cout << "\tDebug Registers Test: d\n";
	cout << "\t\tCheck the debug registers to see if any are non-zero; non-zero debug registers likely means a debugger has been used on the process.\n\n";



	cout << "\tMemory Encryption Test: m\n";
	cout << "\t\tDecrypts memory before performing base test operations on the memory and re-encrypts it after use.\n\n";



	cout << "\tValidate Parent Process Test: p\n";
	cout << "\t\tResolve the parent process name and check if it contains known invalid options such as: 'debug', 'dbg', 'windbg', ollydbg', etc.\n\n";



	cout << "\tSelf-debugging Test: s\n";
	cout << "\t\tCreates a child process that debugs this process to prevent another debugger from attaching to it. Uses SelfDebuggingChild.exe as child process.\n\n";



	cout << "\tTiming Analysis Test: t\n";
	cout << "\t\tMeasures the time it takes work to be completed and if that work takes longer than 0.5 seconds, its likely a debugger has been attached.\n\n";

	cout << endl;

}
