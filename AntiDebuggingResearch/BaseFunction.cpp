#include <vector>
#include <Windows.h>


#pragma optimize( "", off )
void BaseFunction1(std::vector<size_t>& iDataVector, size_t i)
{
	size_t tmp = 0;
	iDataVector.push_back(i);
	for (size_t j = 0; j < 1024; j++)
	{
		tmp = iDataVector.at(i);
		tmp = (tmp * j) % 1024;
		iDataVector.at(i) = tmp;
	}
	
}
#pragma optimize( "", on)

//fast_sample
#pragma optimize( "", off )
void BaseFunction3([[maybe_unused]] std::vector<size_t>& iDataVector, [[maybe_unused]] size_t i)
{
	DWORD temp = 0;
	for (DWORD j = 0; j < (DWORD)1000; j++) temp += j;
}
#pragma optimize( "", on)

//medium_sample
#pragma optimize( "", off )
void BaseFunction4([[maybe_unused]] std::vector<size_t>& iDataVector, [[maybe_unused]] size_t i)
{
	DWORD temp = 0;
	for (DWORD j = 0; j < (DWORD)10000; j++) temp += j;
}
#pragma optimize( "", on)

//slow_sample
#pragma optimize( "", off )
void BaseFunction5([[maybe_unused]] std::vector<size_t>& iDataVector, [[maybe_unused]] size_t i)
{
	DWORD temp = 0;
	for (DWORD j = 0; j < (DWORD)100000; j++) temp += j;
}
#pragma optimize( "", on)