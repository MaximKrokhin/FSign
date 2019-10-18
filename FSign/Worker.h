#pragma once
#include <thread>
#include <atomic>
#include <functional>
#include <memory>

using namespace std;

struct Worker
{
	Worker();
	~Worker();
	void startWork(function<void()> work, size_t sleepingTime);
	void stopWork();
	void wait();

private:
	unique_ptr<thread> _workingThread;
	atomic<bool> _stopflag;
};