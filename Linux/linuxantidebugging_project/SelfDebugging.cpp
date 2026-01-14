#include "BaseTest.hpp"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

void ValidateSelfDebuggingTest(void)
{
	std::vector<size_t> iDataVector = std::vector<size_t>(BUFSIZE);
	size_t tmp = 0;
	std::string functionName = std::string("SelfDebuggingTest");

	ResearchTimer r(functionName+" (Total)");
	for(size_t i=0; i < BUFSIZE; i++)
	{
		ResearchTimer r2(functionName);

		int32_t to_child[2];
		int32_t to_parent[2];
		if(pipe(to_child) < 0)
		{
			std::cout << "failed to create pipe." << std::endl;
			exit(1);
		}

		if(pipe(to_parent) < 0)
		{
			std::cout << "failed to create pipe." << std::endl;
			exit(1);
		}

		pid_t child = fork();
		if(child == 0)
		{
			const int32_t ZERO = 0;
			const int32_t NEGONE = -1;
			int32_t bytesWritten = 0;
			int32_t bytesRead = 0;
			int32_t isDone = 0;
			close(to_child[1]);
			close(to_parent[0]);
			std::cout << "Parent pid: " << getppid() << std::endl;
			int32_t status = ptrace(PTRACE_ATTACH, getppid());
			if(status == -1)
			{
				std::cout << "Child - Being Debugged, oh no!" << std::endl;
				bytesWritten = write(to_parent[1], &NEGONE, sizeof(int32_t));
				std::cout << "child bytes written: " << bytesWritten << std::endl;
				exit(1);
			}
			std::cout << "child status: " << status << std::endl;
			status = ptrace(PTRACE_CONT, getppid(), 0, 0);
			std::cout << "child status CONT: " << status << std::endl;
			bytesWritten = write(to_parent[1], &ZERO, sizeof(int32_t));
			close(to_parent[1]);
			std::cout << "child bytes written: " << bytesWritten << std::endl;
			waitpid(getppid(), nullptr, 0);
			while(isDone == 0)
			{
				bytesRead = read(to_child[0], &isDone, sizeof(int32_t));
				std::cout << "child bytes read: " << bytesRead << std::endl;
			}
			ptrace(PTRACE_DETACH, getppid(), 0, 0);
			exit(0);
			
			

		}
		else
		{
			const int32_t ONE = 1;
			int32_t debugStatus = 2; //Not 0 or -1
			int32_t bytesWritten = 0;
			close(to_parent[1]);
			close(to_child[0]);
			std::cout << "child pid: " << child << std::endl;
			int32_t bytesRead = read(to_parent[0], &debugStatus, sizeof(int32_t));
			close(to_parent[0]);
			std::cout << "bytes read: " << bytesRead << std::endl;
			if(debugStatus == -1)
			{
				std::cout << "Being debugged!!" << std::endl;
				exit(1);
			}
			else if (debugStatus == 0)
			{
				iDataVector.push_back(i);
				for(size_t j=0; j < 1024; j++)
				{
					tmp = iDataVector.at(i);
					tmp = (tmp*j) % 1024;
					iDataVector.at(i) = tmp;
				}

			}
			else
			{
				std::cout << "Invalid Debug Status" << std::endl;
				exit(1);
			}
			bytesWritten = write(to_child[1], &ONE, sizeof(int32_t));
			close(to_child[1]);
			std::cout << "parent bytes written: " << bytesWritten << std::endl;
			wait(NULL);
			r2.stop();

		}
	}
}
