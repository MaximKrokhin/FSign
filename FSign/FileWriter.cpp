#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "FileWriter.h"
#include "Variables.cpp"
using namespace std;
FileWriter::FileWriter(const string& filename, size_t size) : _fileName(filename), _size(size), buffer(size)
{
	newTread();
}
void FileWriter::newTread()
{
	Writer.startWork([this]()
		{
			Create();
		},defaultInterval);
}
bool FileWriter::data_writer(const size_t index, const string& data)
{
	lock_guard<mutex> lockBuff(_mutexBuff);
	buffer[index - _maxIndex] = data;
	return true;
}
void FileWriter::Create()
{
	vector<string> Buffer2;
	{
		lock_guard<mutex> lockStorage(_mutexBuff);
		size_t i = 0;
		for (; i < buffer.size(); ++i)
		{
			if (buffer[i].empty())
				break;
		}
		_maxIndex += i;
		copy(buffer.begin(), buffer.begin() + i, back_inserter(Buffer2));
		buffer.erase(buffer.begin(), buffer.begin() + i);
	}
	lock_guard<mutex> writeLock(_mutexWriter);
	ofstream ofs(_fileName, ios_base::app | ofstream::binary);
	ostream_iterator<string> outIterator(ofs);
	copy(Buffer2.begin(), Buffer2.end(), outIterator);
}