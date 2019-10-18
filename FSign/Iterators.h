#pragma once
#include <string>
#include <memory>
using namespace std;

struct DataIterator
{
	virtual ~DataIterator() {};
	virtual string data_processor(const string& data) = 0;
};
struct WriteIterator
{
	virtual ~WriteIterator() {};
	virtual bool data_writer(const size_t index, const string& data) = 0;
};
struct ReadIterator
{
	virtual ~ReadIterator() {};
	virtual size_t read_data(const size_t offset, char* buf, const size_t size) = 0;
};