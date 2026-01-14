#include "LogFile.hpp"
#include <iostream>
#include <string>
#include "Windows.h"

LogFile::LogFile(std::string fileName, std::string typeName, std::string testName) : mFileName(fileName), mTypeName(typeName), mTestName(testName) 
{
	if (fileName.empty())
	{
		std::cerr << "[!] Unable to open file handle because fileName is empty." << std::endl;
		return;
	}

	mFileHandle = CreateFileA(
		fileName.c_str(),
		GENERIC_WRITE,
		0, //No file sharing
		nullptr, //no security descriptor
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr //No template file
	);

	if (mFileHandle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "[!] Unable to open log file handle, invalid handle detected. GLE=0x" << std::hex << GetLastError() << std::endl;
	}
};

LogFile::~LogFile()
{
	if (mFileHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(mFileHandle);
		return;
	}

	std::cerr << "[!] Unable to close file handle due to invalid value or nullptr." << std::endl;
}

LogFile::LogFile(const LogFile& other) : mFileHandle(other.mFileHandle), mFileName(other.mFileName), mTypeName(other.mTypeName), mTestName(other.mTestName) {};

LogFile& LogFile::operator=(const LogFile& other)
{
	mFileHandle = other.mFileHandle;
	mFileName = other.mFileName;
	mTypeName = other.mTypeName;
	mTestName = other.mTestName;
	return *this;
}

LogFile::LogFile(LogFile&& other) noexcept : mFileHandle(other.mFileHandle), mFileName(other.mFileName), mTypeName(other.mTypeName), mTestName(other.mTestName)
{
	other.mFileHandle = INVALID_HANDLE_VALUE;
	other.mFileName = "";
	other.mTypeName = "";
	other.mTestName = "";
};

LogFile& LogFile::operator=(LogFile&& other) noexcept
{
	std::swap(mFileHandle, other.mFileHandle);
	std::swap(mTypeName, other.mTypeName);
	std::swap(mFileName, other.mFileName);
	std::swap(mTestName, other.mTestName);

	return *this;
}

bool LogFile::Write(std::string content) const
{
	bool returnValue = false;
	DWORD dwNumberBytesWritten = 0;
	returnValue = WriteFile(
		mFileHandle,
		content.c_str(),
		static_cast<DWORD>(content.size()),
		&dwNumberBytesWritten,
		NULL //No Overlapped structure
	);
	if (dwNumberBytesWritten != content.size())
	{
		std::cerr << "[!] WriteFile() failed. GLE=0x" << std::hex << GetLastError() << std::endl;
		std::cerr << "[!] Number of bytes written is not equal to the size of the content." << std::endl;
		std::cerr << content << std::endl;
		std::cerr << "Size: " << std::to_string(content.size()) << ", Bytes Written: " << std::to_string(dwNumberBytesWritten) << std::endl;
		return false;
	}

	if (!returnValue)
	{
		std::cerr << "[!] WriteFile() failed. GLE=0x" << std::hex << GetLastError() << std::endl;
		return false;
	}

	return returnValue;
}