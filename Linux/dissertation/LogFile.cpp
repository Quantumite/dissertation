#include "LogFile.hpp"
#include <iostream>
#include <string>
#include <fstream>

LogFile::LogFile(std::string fileName, std::string typeName, std::string testName) : mFileName(fileName), mTypeName(typeName), mTestName(testName)
{
    if(fileName.empty())
    {
        std::cerr << "[!] Unable to open file handle because fileName is empty." << std::endl;
        return;
    }

    mFileStream.open(fileName);
    if(mFileStream.fail())
    {
        std::cerr << "[!] Unable to open log file handle, invalid handle detected." << std::endl;
    }
}

LogFile::~LogFile()
{
    if(mFileStream.good())
    {
        mFileStream.close();
        return;
    }

    std::cerr << "[!] Unable to close file handle due to invalid value or bad stream." << std::endl;
}

LogFile::LogFile(const LogFile& other) : mFileName(other.mFileName), mTypeName(other.mTypeName), mTestName(other.mTestName) {};

LogFile& LogFile::operator=(const LogFile& other)
{
	mFileName = other.mFileName;
	mTypeName = other.mTypeName;
	mTestName = other.mTestName;
	return *this;
}

LogFile::LogFile(LogFile&& other) noexcept : mFileName(other.mFileName), mTypeName(other.mTypeName), mTestName(other.mTestName)
{
	other.mFileName = "";
	other.mTypeName = "";
	other.mTestName = "";
};

LogFile& LogFile::operator=(LogFile&& other) noexcept
{
	std::swap(mFileStream, other.mFileStream);
	std::swap(mTypeName, other.mTypeName);
	std::swap(mFileName, other.mFileName);
	std::swap(mTestName, other.mTestName);

	return *this;
}

bool LogFile::Write(std::string content) 
{
    mFileStream.write(content.c_str(), content.size());
    if(!mFileStream.fail())
    {
        return true;
    }
    
    std::cout << "Error occurred writing to log file." << std::endl;
    return false;
}