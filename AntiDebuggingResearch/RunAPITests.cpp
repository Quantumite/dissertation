#include "IsDebuggerPresent.hpp"
#include "NtGlobalFlag.hpp"
#include "HeapFlag.hpp"
#include "CsrGetProcessId.hpp"
#include "EventPairHandles.hpp"
#include "OutputDebugString.hpp"
#include "NtQueryObject.hpp"
#include "NtSetInformationThread.hpp"
#include "NtQueryInformationProcess.hpp"
#include "CheckRemoteDebuggerPresent.hpp"
#include "DebugRegisters.hpp"
#include "NtSetDebugFilterState.hpp"

namespace API
{
	void RunAPITests()
	{
		//IsDebuggerPresent Test
		IsDebuggerPresentTest idpt = IsDebuggerPresentTest();
		idpt.PreRun();
		idpt.RunTest();
		idpt.PostRun();

		//NtGlobalFlag Test
		NtGlobalFlagTest ngft = NtGlobalFlagTest();
		ngft.PreRun();
		ngft.RunTest();
		ngft.PostRun();

		//HeapFlag Test
		HeapFlagTest hft = HeapFlagTest();
		hft.PreRun();
		hft.RunTest();
		hft.PostRun();

		//CsrGetProcessId Test
		CsrGetProcessIdTest cgpit = CsrGetProcessIdTest();
		cgpit.PreRun();
		cgpit.RunTest();
		cgpit.PostRun();

		//EventPariHandles Test - @TODO
		EventPairHandlesTest epht = EventPairHandlesTest();
		epht.PreRun();
		epht.RunTest();
		epht.PostRun();

		//OutputDebugString Test
		OutputDebugStringTest odst = OutputDebugStringTest();
		odst.PreRun();
		odst.RunTest();
		odst.PostRun();

		//NtQueryObject Test
		NtQueryObjectTest nqot = NtQueryObjectTest();
		nqot.PreRun();
		nqot.RunTest();
		nqot.PostRun();

		//NtSetInformationThread Test
		NtSetInformationThreadTest nsit = NtSetInformationThreadTest();
		nsit.PreRun();
		nsit.RunTest();
		nsit.PostRun();

		//NtQueryInformationProcess Test
		NtQueryInformationProcessTest nqipt = NtQueryInformationProcessTest();
		nqipt.PreRun();
		nqipt.RunTest();
		nqipt.PostRun();

		//CheckRemoteDebuggerPresent Test
		CheckRemoteDebuggerPresentTest crdpt = CheckRemoteDebuggerPresentTest();
		crdpt.PreRun();
		crdpt.RunTest();
		crdpt.PostRun();

		//Debug Registers Test
		DebugRegistersTest drt = DebugRegistersTest();
		drt.PreRun();
		drt.RunTest();
		drt.PostRun();

		//NtSetDebugFilterState Test
		NtSetDebugFilterStateTest nsdfst = NtSetDebugFilterStateTest();
		nsdfst.PreRun();
		nsdfst.RunTest();
		nsdfst.PostRun();

	}
}