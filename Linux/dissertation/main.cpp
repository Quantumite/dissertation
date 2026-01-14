#include <iostream>
#include "PrintUsage.hpp"
#include "BaseTest.hpp"
#include "RunTimingTests.hpp"
#include "RunMiscTests.hpp"
#include "RunScanningTests.hpp"
#include "RunExceptionTests.hpp"

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
			case 'b':
				 //BaseTest
				 BaseTest();
				 break;
			
			case 'e':
				//exception tests
				Exception::RunExceptionTests();
				break;

			case 'm':
				 //misc tests
				 Misc::RunMiscTests();
				 break;

			case 's':
				 //scanning tests
				 Scanning::RunScanningTests();
				 break;

			case 't':
		  	  //timing tests
			  Timing::RunTimingTests();
			  break;

			default:
				 std::cout << "Invalid option." << std::endl;
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
