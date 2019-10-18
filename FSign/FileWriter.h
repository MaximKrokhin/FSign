#pragma once
#include <deque>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "Iterators.h"
#include "Worker.h"

struct FileWriter : WriteIterator
{
private:
	string _fileName;
	size_t _size;
	size_t _maxIndex = 0;
	deque<string> buffer;
	mutex _mutexBuff;
	mutex _mutexWriter;
	Worker Writer;
public:
	FileWriter(const string& _filename, size_t _size);
	bool data_writer(const size_t index, const string& data) override;
private:
	void newTread();
	void Create();
};
