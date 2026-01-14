#pragma once
#pragma once
#include "LogFile.hpp"


//Thanks to https://evilcodecave.wordpress.com/tag/rtlcreatequerydebugbuffer/

// RtlQueryProcessDebugInformation.DebugInfoClassMask constants
#define PDI_MODULES                       0x01
#define PDI_BACKTRACE                     0x02
#define PDI_HEAPS                         0x04
#define PDI_HEAP_TAGS                     0x08
#define PDI_HEAP_BLOCKS                   0x10
#define PDI_LOCKS                         0x20

typedef struct _DEBUG_BUFFER {
	HANDLE  SectionHandle;
	PVOID  SectionBase;
	PVOID  RemoteSectionBase;
	ULONG  SectionBaseDelta;
	HANDLE  EventPairHandle;
	ULONG  Unknown[2];
	HANDLE  RemoteThreadHandle;
	ULONG  InfoClassMask;
	ULONG  SizeOfInfo;
	ULONG  AllocatedSize;
	ULONG  SectionSize;
	PVOID  ModuleInformation;
	PVOID  BackTraceInformation;
	PVOID  HeapInformation;
	PVOID  LockInformation;
	PVOID  Reserved[8];
} DEBUG_BUFFER, * PDEBUG_BUFFER;

typedef struct _DEBUG_HEAP_INFORMATION
{
	ULONG Base; // 0x00
	ULONG Flags; // 0x04
	USHORT Granularity; // 0x08
	USHORT Unknown; // 0x0A
	ULONG Allocated; // 0x0C
	ULONG Committed; // 0x10
	ULONG TagCount; // 0x14
	ULONG BlockCount; // 0x18
	ULONG Reserved[7]; // 0x1C
	PVOID Tags; // 0x38
	PVOID Blocks; // 0x3C
} DEBUG_HEAP_INFORMATION, * PDEBUG_HEAP_INFORMATION;

typedef PDEBUG_BUFFER(*pRtlCreateQueryDebugBuffer)(ULONG size, BOOLEAN EventPair);
typedef NTSTATUS(*pRtlQueryProcessDebugInformation)(ULONG procId, ULONG DebugInfoClassMask, PDEBUG_BUFFER dbgbuf);

namespace API {
	class EventPairHandlesTest {
	public:
		EventPairHandlesTest();

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
		LogFile lf;
	};

}
