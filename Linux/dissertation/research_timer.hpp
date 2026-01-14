#pragma once
#include <iostream>
#include <time.h>
#include <string>

/*
 * Some implementation taken from www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
 * */ 
using namespace std;

class ResearchTimer
{
	public:
		ResearchTimer() noexcept;
		ResearchTimer(std::string title) noexcept;

		~ResearchTimer() noexcept;

		void stop() noexcept;
		void start(std::string title) noexcept;

		uint64_t diff(timespec *start, timespec *end);

	private:
		timespec mStartTime;
		timespec mStopTime;
		uint64_t mDiffTimeNS;
		std::string mTitle;
		bool mStopped;
};
