#include <cxxopts.hpp>

int main(int argc, char* argv[])
{
	cxxopts::Options options("xut", "xut compiles xaml files into intermediate cpp/h files");
	options.add_options()
		("o,output", "output cpp")
		("i,input", "input xaml")
		("h,header", "header file");

	auto result = options.parse(argc, argv);
	return 0;
}