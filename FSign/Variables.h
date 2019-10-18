#pragma once
#include <string>
#include <filesystem>

using namespace std;

struct Variables
{
	Variables(int argc, char** argv);
	~Variables();
	string getInputPath();
	string getOutputPath();
	size_t getChunkSize();
	size_t inputFileSize();
	size_t AmountofBlocks();
	

private:
	void InputPathExists(string & path);
private:
	string _inputPath;
	string _outputPath;
	size_t _chunkSize;
	size_t _maxIndex;
	size_t _inputFileSize;
};