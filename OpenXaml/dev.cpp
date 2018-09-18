#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Parser/Parser.h"

using namespace std;

int main(int argc, char *argv[], char *envp[])
{
	std::string inputFile;
	for (int i = 1; i < argc; i++)
	{
		string parameter(argv[i]);
		if (parameter == "-i")
		{
			inputFile = argv[++i];
		}
		else
		{
			cerr << "Unrecognized input parameter: " << argv[i] << "\n";
			return EXIT_FAILURE;
		}
	}
	bool error = false;
	if (inputFile == "")
	{
		cerr << "Input file is required\n";
		error = true;
	}
	if (error)
	{
		return EXIT_FAILURE;
	}

	string file = OpenXaml::Parser::ReadFile(inputFile);

	
	cout << argv[0];
	cout << "done";
}