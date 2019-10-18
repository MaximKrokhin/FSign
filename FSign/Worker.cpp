#include <chrono>
#include "Worker.h"
#include <stdexcept>
using namespace std;
Worker::Worker() : _stopflag(false) {};
Worker::~Worker()
{
	stopWork();
}
void Worker::startWork(function<void()> work, size_t sleepingTime)
{
	if (_workingThread = nullptr)
		throw runtime_error("It's not time yet");
	_workingThread.reset(new thread([this, work, sleepingTime]()
		{
			while (!_stopflag)
			{
				this_thread::sleep_for(chrono::milliseconds(sleepingTime));
				work();
			}
			//work();
		}));

}
void Worker::stopWork()
{
	_stopflag = true;
}
void Worker::wait()
{
	if (_workingThread)
		_workingThread->join();
}