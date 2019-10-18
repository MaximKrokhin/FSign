#pragma once
#include <fstream>
#include <mutex>
#include <memory>
#include "Iterators.h"
using namespace std;
struct FileReader : ReadIterator {
	FileReader(const string& filename);
	virtual size_t read_data(const size_t offset, char* buf, const size_t size) override;
private:
	ifstream _stream;
	mutex read_mutex;
};