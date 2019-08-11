#include <cxxopts.hpp>
#include <string>
#include "internal/XamlElement.h"
#include "internal/XamlClass.h"
using namespace std;

int main(int argc, char* argv[])
{
	std::string inputFile;
	std::string outputFile;
	cxxopts::Options options("xut", "xut compiles xaml files into intermediate hpp files");
	options.add_options()
		("o,output", "output hpp", cxxopts::value<std::string>(outputFile))
		("i,input", "input xaml", cxxopts::value<std::string>(inputFile))
		("h,header", "header file");

	auto result = options.parse(argc, argv);
	try
	{
		xut::elements::XamlClass* c = new xut::elements::XamlClass(inputFile);
		c->WriteToFile(outputFile);
	}
	catch (int error)
	{
		std::cerr << "Failed\n";
		return -1;
	}

	return 0;
}