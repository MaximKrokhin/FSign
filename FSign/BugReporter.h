#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <exception>
using namespace std;

struct BugReporter
{
	void addtolist(exception& e);
	void showAll();

private:
	queue<string> Errors;
	mutex _mutex;
};