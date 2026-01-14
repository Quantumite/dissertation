#pragma once
#include <Windows.h>

namespace Scanning
{
	class Fletcher
	{
	public:
		Fletcher();
		Fletcher(PVOID data, size_t length);
		Fletcher(PVOID start, PVOID end);
		WORD GetChecksum() const;

	private:
		void Compute(PVOID data, size_t length);
		WORD mChecksum = 0;
	};
}
