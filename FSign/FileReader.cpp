#include <fstream>
#include <string>
#include "Variables.cpp"
#include "FileReader.h"

FileReader::FileReader(const string& filename) : _stream(filename, ifstream::binary)
{
	if (!_stream)
		throw runtime_error("Can't read this file");
}

size_t FileReader::read_data(const size_t offset, char* buf, const size_t size)
{
	lock_guard<mutex> lock(read_mutex);
	_stream.seekg(offset, ios_base::beg);
	_stream.read(buf, size);
	if (_stream.bad())
		throw runtime_error("Reading failed");
	return _stream.gcount();
}