#pragma once
#include "LogFile.hpp"

#define DEBUG_OBJECT_NAME L"DebugObject"

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING;

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation = 0,
	ObjectNameInformation = 1,
	ObjectTypeInformation = 2,
	ObjectAllTypesInformation = 3,
	ObjectHandleInformation = 4
} OBJECT_INFORMATION_CLASS;


typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
} OBJECT_TYPE_INFORMATION, * POBJECT_TYPE_INFORMATION;

typedef struct _OBJECT_ALL_TYPES_INFORMATION {
	ULONG NumberOfObjectTypes;
	OBJECT_TYPE_INFORMATION ObjectTypeInformation[1];
} OBJECT_ALL_TYPES_INFORMATION, * POBJECT_ALL_TYPES_INFORMATION;

typedef NTSTATUS(*pNtQueryObject)(HANDLE Handle, OBJECT_INFORMATION_CLASS ObjectInformationClass,	PVOID ObjectInformation,	ULONG ObjectInformationLength, 	PULONG ReturnLength);

namespace API {
	class NtQueryObjectTest {
	public:
		NtQueryObjectTest();

		bool PreRun()
		{
			return true;
		}
		void RunTest();
		bool PostRun()
		{
			return true;
		}

	private:
		bool _run_test();
		LogFile lf;
	};

}

