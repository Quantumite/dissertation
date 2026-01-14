#pragma once
#include <string>
#include <fstream>

class LogFile
{
public:
	LogFile() {};
	LogFile(std::string fileName, std::string typeName, std::string testName);
	~LogFile();
	LogFile(const LogFile& other);
	LogFile(LogFile&& other) noexcept;
	LogFile& operator=(const LogFile& other);
	LogFile& operator=(LogFile&& other) noexcept;

	std::string GetTestType() {
		return mTypeName;
	}

	std::string GetTestName() {
		return mTestName;
	}
	
	bool Write(std::string content);

private:
	std::ofstream mFileStream;
	std::string mFileName = "";
	std::string mTypeName = "";
	std::string mTestName = "";
};