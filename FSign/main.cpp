#include <iostream>
#include "Signature.h"
#include "Signature.cpp"
#include "Worker.cpp"
using namespace std;
int main(int argc, char** argv)
{
	try
	{
		Signature ({ argc, argv });
	}
	catch (const std::exception & e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}