#pragma once
#include <cstdint>

namespace Scanning
{
    template <typename T>
	class Fletcher
	{
	public:

        Fletcher<T>()
        {
	        mChecksum = 0;
        }

        Fletcher<T>(T data, size_t length)
        {
	        Compute(data, length);
        }

        uint16_t GetChecksum() const
        {
	        return mChecksum;
        }


	private:
        void Compute(T data, size_t length)
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
		uint16_t mChecksum = 0;
	};
}