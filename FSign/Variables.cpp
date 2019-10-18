#include "Variables.h"
#include <filesystem>
#include <string>

using namespace std;

const size_t defaultBlockSize = 1 + 1024 * 1024;
const size_t defaultBufferSize = 5 * 1024 * 1024;
const size_t defaultInterval = 100;

Variables::Variables(int argc, char** argv) {
		_inputPath = argv[1];
		_outputPath = argv[2];
		_chunkSize = defaultBlockSize > atoi(argv[3]) ? atoi(argv[3]) : defaultBlockSize;
		InputPathExists(_inputPath);
		_inputFileSize = filesystem::file_size(_inputPath);
		_maxIndex = _inputFileSize / _chunkSize;
		if (!isdigit(_chunkSize))
		{
			throw runtime_error("Incorrect blocksize");
		}
		
}

string Variables::getInputPath()
{
	return _inputPath;
}

string Variables::getOutputPath()
{
	return _outputPath;

}

size_t Variables::inputFileSize() 
{
	return _inputFileSize;
}

size_t Variables::AmountofBlocks()
{
	return _maxIndex;
}

size_t Variables::getChunkSize()
{
	return _chunkSize;

}

void Variables::InputPathExists(string& path) 
{
	if (!filesystem::exists(path)) 
	{
		filesystem::path pathtoFile(filesystem::current_path());
		pathtoFile += filesystem::path::preferred_separator;
		pathtoFile += path;
		if (!filesystem::exists(pathtoFile))
			throw std::runtime_error("No such file or directory");
	}
}
