#include <iostream>
#include <vector>
#include <Windows.h>
#include "Timing.hpp"
#include "BaseTest.hpp"
#include "NtQueryObject.hpp"
#include "BaseFunction.hpp"

//Based on https://gist.github.com/soxfmr/16c495d6e4ad99e9e46f5bfd558d152f

API::NtQueryObjectTest::NtQueryObjectTest() {
	lf = LogFile("ntqueryobject.log", "API", "NtQueryObject");
}

bool API::NtQueryObjectTest::_run_test()
{
	pNtQueryObject NtQueryObject = nullptr;
	POBJECT_TYPE_INFORMATION pObjectTypeInfo = nullptr;
	POBJECT_ALL_TYPES_INFORMATION pObjectAllTypesInfo = nullptr;

	UCHAR* pNextTypeLocation = nullptr;
	UCHAR* pObjectTypeLocation = nullptr;

	DWORD dwObjAllTypesLen = 0;
	PVOID pObjectAllTypesBuffer = nullptr;

	NtQueryObject = (pNtQueryObject)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryObject");
	if (!NtQueryObject)
	{
		std::cout << "Unable to resolve NtQueryObject() from ntdll.dll" << std::endl;
		exit(1);
	}

	//Used to get size of ObjectAllTypesInformation
	NtQueryObject(NULL, ObjectAllTypesInformation, &dwObjAllTypesLen, sizeof(dwObjAllTypesLen), &dwObjAllTypesLen);

	//Allocate space after unsuccessful first call that gives size
	pObjectAllTypesBuffer = VirtualAlloc(nullptr, dwObjAllTypesLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	NTSTATUS status = NtQueryObject((HANDLE)-1, ObjectAllTypesInformation, pObjectAllTypesBuffer, dwObjAllTypesLen, nullptr);
	if (status)
	{
		if (pObjectAllTypesBuffer) VirtualFree(pObjectAllTypesBuffer, 0, MEM_RELEASE);
		exit(1);
	}

	pObjectAllTypesInfo = (POBJECT_ALL_TYPES_INFORMATION)pObjectAllTypesBuffer;
	pObjectTypeLocation = (UCHAR*)pObjectAllTypesInfo->ObjectTypeInformation;

	for (size_t j = 0; j < pObjectAllTypesInfo->NumberOfObjectTypes; j++)
	{
		pObjectTypeInfo = (POBJECT_TYPE_INFORMATION)pObjectTypeLocation;
		if (wcscmp(DEBUG_OBJECT_NAME, pObjectTypeInfo->TypeName.Buffer) == 0)
		{
			return pObjectTypeInfo->TotalNumberOfObjects > 0 ? true : false;	
		}

		//Move to next object by moving pointer past buffer+length of previous object
		pObjectTypeLocation = (UCHAR*)pObjectTypeInfo->TypeName.Buffer;
		pObjectTypeLocation += pObjectTypeInfo->TypeName.MaximumLength;

		//Align address
		pNextTypeLocation = (UCHAR*)((ULONGLONG)pObjectTypeLocation & ((~sizeof(PVOID))+1));

		//Fixup address if alignment makes address too small
		if (pNextTypeLocation < pObjectTypeLocation) pNextTypeLocation += sizeof(PVOID);

		pObjectTypeLocation = pNextTypeLocation;
	}

	if (pObjectAllTypesBuffer) VirtualFree(pObjectAllTypesBuffer, 0, MEM_RELEASE);

	return false;
}

void API::NtQueryObjectTest::RunTest()
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Measure
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (_run_test())
		{
			std::cout << "[NtQueryObjectTest] Debugger detected. Exiting.\n" << std::endl;
			return;
		}

		BaseFunction5(iDataVector, i);
		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}