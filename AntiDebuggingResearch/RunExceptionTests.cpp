#include <iostream>
#include "GuardPage.hpp"
#include "Int3.hpp"
#include "UnhandledExceptionFilter.hpp"
#include "CloseHandle.hpp"
#include "Int2d.hpp"
#include "TrapFlag.hpp"

namespace Exception {

	void RunExceptionTests()
	{
		//GuardPage Test
		std::cout << "Starting GuardPageTest..." << std::endl;
		GuardPageTest gpt = GuardPageTest();
		gpt.PreRun();
		gpt.RunTest();
		gpt.PostRun();

		//Int3 Test
		std::cout << "Starting Int3Test..." << std::endl;
		Int3Test i3t = Int3Test();
		i3t.PreRun();
		i3t.RunTest();
		i3t.PostRun();

		//UnhandledExceptionFilter Test
		std::cout << "Starting UnhandledExceptionFilterTest..." << std::endl;
		UnhandledExceptionFilterTest ueft = UnhandledExceptionFilterTest();
		ueft.PreRun();
		ueft.RunTest();
		ueft.PostRun();

		//CloseHandle Test
		std::cout << "Starting CloseHandleTest..." << std::endl;
		CloseHandleTest cht = CloseHandleTest();
		cht.PreRun();
		cht.RunTest();
		cht.PostRun();

		//Int2d Test
		std::cout << "Starting Int2dTest..." << std::endl;
		Int2dTest i2dt = Int2dTest();
		i2dt.PreRun();
		i2dt.RunTest();
		i2dt.PostRun();

		//Trap Flag Test
		std::cout << "Starting TrapFlagTest..." << std::endl;
		TrapFlagTest tft = TrapFlagTest();
		tft.PreRun();
		tft.RunTest();
		tft.PostRun();

		return;
	}
}
