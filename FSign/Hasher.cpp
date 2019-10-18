#include <iostream>
#include <functional>
#include <string>
#include "Hasher.h"
using namespace std;
string Hasher::data_processor(const string& data)
{
	hash<string> hash_fn;
	size_t result;
	result ^= hash_fn(data);
	return to_string(result);
}
