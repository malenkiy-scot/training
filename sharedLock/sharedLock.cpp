// sharedLock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct mytime {
	int ms_;
	mytime(int ms): ms_(ms) {}
	int total_milliseconds() const {return ms_;}
};

boost::shared_mutex sm;

void lockFunc()
{
	boost::upgrade_lock<boost::shared_mutex> preWriteLock();
	{
		boost::shared_lock<boost::shared_mutex> readLock(sm);
		std::cout << "My thread id before: " << boost::this_thread::get_id() << std::endl;
		boost::this_thread::sleep(mytime(500));
		preWriteLock = boost::upgrade_lock<boost::shared_mutex>(sm);
	}
	{
		boost::upgrade_to_unique_lock<boost::shared_mutex> writeLock(preWriteLock);
		std::cout << "My thread id after: " << boost::this_thread::get_id() << std::endl;
	}
}

void threadFunc()
{
	lockFunc();
	boost::this_thread::sleep(mytime(500));
}

int _tmain(int argc, _TCHAR* argv[])
{
	boost::thread t1(threadFunc);
	boost::thread t2(threadFunc);
	std::cout << "Main thread id: " << boost::this_thread::get_id() << std::endl;
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
	boost::this_thread::sleep(mytime(500));
}
