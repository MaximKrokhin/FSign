#include <iostream>
#include "BugReporter.h"
using namespace std;

void BugReporter::addtolist(exception & e)
{
	lock_guard<mutex> lock(_mutex);
	Errors.push(e.what());
}

void BugReporter::showAll()
{
	lock_guard<mutex> lock(_mutex);
	if (Errors.empty())
		return;
	for (int i = 0; i != Errors.size() - 1;++i)
	{
		string error = Errors.front();
		Errors.pop();
		cerr << error << "\n";
	}
}