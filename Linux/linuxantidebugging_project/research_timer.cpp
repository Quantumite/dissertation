#include "research_timer.hpp"

/*
 * Some implementation taken from www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
 * */ 
using namespace std;

ResearchTimer::ResearchTimer() noexcept
{
	cout << "Starting Research Timer" << endl;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(this->mStartTime));
}

ResearchTimer::	ResearchTimer(std::string title) noexcept
{
	cout << "Starting Researcher Timer (" << title << ")" << endl;
	this->mTitle = title;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(this->mStartTime));
}

ResearchTimer::~ResearchTimer() noexcept
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(this->mStopTime));

	//mStopTime will become invalid when the destructor is called after stop()
	// but that's ok because we're already calculated the difference.
	if(this->mStopped) return;

	if(!this->mTitle.empty())
	{
		cout << "Stopping Research Timer (" << this->mTitle << ")\n";
	}
	else
	{
		cout << "Stopping Research Timer.\n";
	}
	mDiffTimeNS = diff(&(this->mStartTime), &(this->mStopTime));
	cout << "Time difference is " << this->mDiffTimeNS << "(ns)" << endl;
}

void ResearchTimer::start(std::string title) noexcept
{
	this->mStartTime = {0,0};
	this->mStopTime = {0,0};
	this->mStopped = false;
	this->mDiffTimeNS = 0;

	cout << "Starting Researcher Timer (" << title << ")" << endl;
	this->mTitle = title;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(this->mStartTime));

}

void ResearchTimer::stop() noexcept
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(this->mStopTime));
	if(!this->mTitle.empty())
	{
		cout << "Stopping Research Timer (" << this->mTitle << ")\n";
	}
	else
	{
		cout << "Stopping Research Timer.\n";
	}
	this->mDiffTimeNS = diff(&(this->mStartTime), &(this->mStopTime));
	cout << "Time difference is " << this->mDiffTimeNS << "(ns)" << endl;
	this->mStopped = true;
}

uint64_t ResearchTimer::diff(timespec *start, timespec *end)
{
	timespec temp;
	if((end->tv_nsec - start->tv_nsec) < 0)
	{
		temp.tv_sec = end->tv_sec - start->tv_sec -1;
		temp.tv_nsec = 1000000000 + end->tv_nsec - start->tv_nsec;
	}
	else
	{
		temp.tv_sec = end->tv_sec - start->tv_sec;
		temp.tv_nsec = end->tv_nsec - start->tv_nsec;
	}

	return static_cast<uint64_t>(1000000000*temp.tv_sec + temp.tv_nsec);	

}
