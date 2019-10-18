#pragma once
#include <string>
#include "Iterators.h"
using namespace std;
struct Hasher : DataIterator
{
	string data_processor(const string& data) override;
};
