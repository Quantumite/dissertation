#include <iostream>
#include "research_timer.hpp"
#include "PrintUsage.hpp"
#include "BaseTest.hpp"
#include "IsTracerPidNonzero.hpp"
#include "TimingAnalysis.hpp"
#include "CodeObfuscation.hpp"
#include "DebugRegisters.hpp"
#include "ParentProcess.hpp"
#include "SelfDebugging.hpp"
#include "MemoryEncryption.hpp"


int main(int argc, char* argv[])
{
	 if(argc == 1)
	 {
		 PrintUsage();
		 exit(0);
	 }
	 else if (argc == 2)
	 {
		 char option  = argv[1][0];
		 switch(option)
		 {
			case 'a':
				 //Linux equivalent of IsDebuggerPresent
				 AntiDebugger_IsTracerPidNonzero();
				 break;

			case 'b':
				 //BaseTest
				 BaseTest();
				 break;

			case 'c':
				 //Code Obfuscation
				 ValidateCodeObfuscationTest();
				 break;

			case 'd':
				 //Debug Registers
				 //ValidateDebugRegistersCheck();
				 std::cout << "Unimplemented." << std::endl;
				 break;

			case 'm':
				 //memory encryption test
				 ValidateMemoryEncryptionTest();
				 break;

			case 'p':
				 //Validate parent process
				 RunParentProcessCheck();
				 break;

			case 's':
				 //self-debugging test
				 ValidateSelfDebuggingTest();
				 break;

			case 't':
				 //validate timing analysis
				 ValidateTimingAnalysis();
				 break;

			default:
				 std::cout << "Invalid option." << endl;
				 PrintUsage();
				 exit(1);
		 }
	 }
	 else
	 {
		 std::cout << "Invalid commandline." << std::endl;
		 PrintUsage();
		 exit(1);
	 }
	 exit(0);
}
