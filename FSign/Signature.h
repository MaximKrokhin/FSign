#pragma once
#include <thread>
#include "Variables.h"
#include "ThreadPool.h"
#include "BugReporter.h"
#include "Iterators.h"
using namespace std;
using ReadPtr = shared_ptr<ReadIterator>;
using WritePtr = shared_ptr<WriteIterator>;
using DataProcessorPtr = shared_ptr<DataIterator>;
struct Signature
{
private:
	Variables _variables;
	ThreadPool threadpool;
	BugReporter bugreporter;
public:
	Signature(Variables&& variables);
	void wait();
	void stop();
private:
	ReadPtr create_reader( Variables& variables);
	WritePtr create_writer( Variables& variables);
	DataProcessorPtr create_processor( Variables& variables);

};

