#include "CodeChecksum.hpp"
#include "Int3Scan.hpp"
#include "ParentProcess.hpp"
#include "EnumProcess.hpp"

namespace Scanning {

	void RunScanningTests()
	{
		//CodeChecksum Test
		CodeChecksumTest cct = CodeChecksumTest();
		cct.PreRun();
		cct.RunTest();
		cct.PostRun();

		//Int3Scan Test
		Int3ScanTest i3st = Int3ScanTest();
		i3st.PreRun();
		i3st.RunTest();
		i3st.PostRun();

		//Parent Process Test
		ParentProcessTest ppt = ParentProcessTest();
		ppt.PreRun();
		ppt.RunTest();
		ppt.PostRun();

		//Process Enum Test
		EnumProcessTest ept = EnumProcessTest();
		ept.PreRun();
		ept.RunTest();
		ept.PostRun();

		
		
		

		return;
	}
}