#include "Fletcher.hpp"
#include <Windows.h>

Scanning::Fletcher::Fletcher()
{
	mChecksum = 0;
}

Scanning::Fletcher::Fletcher(PVOID data, size_t length)
{
	Compute(data, length);
}

Scanning::Fletcher::Fletcher(PVOID start, PVOID end)
{
	size_t length = static_cast<size_t>(reinterpret_cast<uintptr_t>(end) - reinterpret_cast<uintptr_t>(start));
	Compute(start, length);
}

WORD Scanning::Fletcher::GetChecksum() const
{
	return mChecksum;
}

void Scanning::Fletcher::Compute(PVOID data, size_t length)
{
	WORD first = 0;
	WORD second = 0;
	char* localData = (char*)data;

	for (size_t i = 0; i < length; i++)
	{
		first = (first + localData[i]) % 255;
		second = (second + first) % 255;
	}

	mChecksum = MAKEWORD(first, second);
}