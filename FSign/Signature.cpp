#include "Signature.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Hasher.h"
using namespace std;
Signature::Signature( Variables&& variables) : _variables(variables), threadpool(thread::hardware_concurrency())
{
	ReadPtr reader = create_reader(_variables);
	WritePtr writer = create_writer(_variables);
	const size_t _chunkSize = _variables.getChunkSize();
	const size_t _maxIndex = _variables.AmountofBlocks();
	for (int i = 0; i <= _maxIndex; ++i)
	{
		threadpool.add([this, i, _chunkSize, reader, writer]()
			{
				try
				{
					unique_ptr<char[]> buf(new char[_chunkSize]);
					const size_t alreadyRead = reader->read_data(_chunkSize * i, buf.get(), _chunkSize);
					string data(buf.get(), alreadyRead);
					DataProcessorPtr processor = create_processor(_variables);
					string hash = processor->data_processor(data);
					writer->data_writer(i, hash);
				}
				catch (exception & e)
				{
					bugreporter.addtolist(e);
					stop();
				}
			});
	}
}

void Signature::wait()
{
	threadpool.waitAll();
	bugreporter.showAll();
}

void Signature::stop()
{
	threadpool.stopIt();
}

ReadPtr Signature::create_reader( Variables& variables)
{
	return make_shared<FileReader>(variables.getInputPath());
}

WritePtr Signature::create_writer(Variables& variables)
{
	return make_shared<FileWriter>(variables.getOutputPath(), variables.AmountofBlocks() + 1);
}
DataProcessorPtr Signature::create_processor(Variables& variables)
{
	return make_shared<Hasher>();
}