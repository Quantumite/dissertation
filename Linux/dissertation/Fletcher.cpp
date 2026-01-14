#include <cstddef>
#include <cstdint>
#include "Fletcher.hpp"

Scanning::Fletcher::Fletcher()
{
	mChecksum = 0;
}

Scanning::Fletcher::Fletcher(const void *data, size_t length)
{
	Compute(data, length);
}

uint16_t Scanning::Fletcher::GetChecksum() const
{
	return mChecksum;
}

void Scanning::Fletcher::Compute(const void* data, size_t length)
{
	uint16_t first = 0;
	uint16_t second = 0;
	char* localData = (char*)data;

	for (size_t i = 0; i < length; i++)
	{
		first = (first + localData[i]) % 255;
		second = (second + first) % 255;
	}

	mChecksum = (first & 0xff) | ((second & 0xff) << 8);
}