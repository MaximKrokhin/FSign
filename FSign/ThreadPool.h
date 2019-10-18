#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
using namespace std;
struct ThreadPool
{
	ThreadPool(size_t);
	template<class F, class... Args>
	auto add(F&& f, Args&&... args)->future<typename result_of<F(Args...)>::type>;
	~ThreadPool();
	void stopIt();
	void waitAll();
private:
	vector< thread > workers;
	queue< function<void()> > tasks;
	mutex queue_mutex;
	condition_variable condition;
	bool stop;
};