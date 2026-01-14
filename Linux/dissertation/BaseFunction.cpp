#include "BaseFunction.hpp"

#pragma optimize( "", off )
void BaseFunction1(std::vector<unsigned char>& iDataVector, std::size_t i)
{
	uint8_t tmp = 0;
	iDataVector.push_back((uint8_t)i);
	for (std::size_t j = 0; j < 1024; j++)
	{
		tmp = iDataVector.at(i);
		tmp = (tmp * j) % 1024;
		iDataVector.at(i) = tmp;
	}
	
}

void BaseFunction1(std::vector<std::size_t>& iDataVector, std::size_t i)
{
	std::size_t tmp = 0;
	iDataVector.push_back(i);
	for (std::size_t j = 0; j < 1024; j++)
	{
		tmp = iDataVector.at(i);
		tmp = (tmp * j) % 1024;
		iDataVector.at(i) = tmp;
	}
	
}
#pragma optimize( "", on)

//fast_sample
#pragma optimize( "", off )
void BaseFunction3([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)1000; j++) temp += j;
}

void BaseFunction3_CodeObfuscation([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)1000; j+=2) temp += j + j + 1;
}

void BaseFunction3([[maybe_unused]] std::vector<uint8_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)1000; j++) temp += j;
}
#pragma optimize( "", on)

//medium_sample
#pragma optimize( "", off )
void BaseFunction4([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)10000; j++) temp += j;
}

void BaseFunction4_CodeObfuscation([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)10000; j++) temp += j;
}

void BaseFunction4([[maybe_unused]] std::vector<uint8_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)10000; j++) temp += j;
}
#pragma optimize( "", on)

//slow_sample
#pragma optimize( "", off )
void BaseFunction5([[maybe_unused]] std::vector<std::size_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)100000; j++) temp += j;
}

void BaseFunction5([[maybe_unused]] std::vector<uint8_t>& iDataVector, [[maybe_unused]] std::size_t i)
{
	uint32_t temp = 0;
	for (uint32_t j = 0; j < (uint32_t)100000; j++) temp += j;
}
#pragma optimize( "", on)