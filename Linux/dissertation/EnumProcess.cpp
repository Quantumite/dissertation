#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "EnumProcess.hpp"
#include "BaseTest.hpp"
#include "BaseFunction.hpp"

Scanning::EnumProcessTest::EnumProcessTest()
{
	lf = LogFile("enumprocess.log", "Scanning", "EnumProcess");
}

bool Scanning::EnumProcessTest::ValidateProcessCheck(void)
{
    const std::string proc_dir = "/proc";
    const std::filesystem::path status_file= "/status";
    for(const auto& entry : std::filesystem::directory_iterator(proc_dir))
    {
	    std::string line;
        std::filesystem::path file_path = entry.path();
        file_path += status_file;
	    std::ifstream file(file_path);

	    for(std::string line; std::getline(file, line);)
	    {
		    std::istringstream _stream(line);
		    std::string tag, value;
		    _stream >> tag >> value;
		    if(tag == "Name:")
            {
                for(const auto& bad : Scanning::EnumProcessTest::BADPROCESSNAMES)
                {
                    if(value.find(bad) != std::string::npos)
                    {
                        return true;
                    }

                }
            }
	    }
    }
    return false;
}

void Scanning::EnumProcessTest::RunTest(void)
{
	//Initialize Buffer
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	AntiDebuggingTimer adt = AntiDebuggingTimer();

	//Timing
	for (size_t i = 0; i < LOOPSIZE; i++)
	{
		adt.AntiDebugging_TimeStart();
		if (ValidateProcessCheck())
		{
			std::cout << "[EnumProcessTest] Debugger detected. Exiting.\n" << std::endl;
			exit(1);
		}

		BaseFunction3(iDataVector, i);

		adt.AntiDebugging_TimeStop();
		lf.Write(adt.PrintResults(lf));
	}
}