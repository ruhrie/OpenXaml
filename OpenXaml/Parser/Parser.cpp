#include "Parser/Parser.h"
#include <string>
#include <fstream>

using namespace std;
namespace OpenXaml {
	namespace Parser {
		string ReadFile(string input)
		{
			string fileText;
			ifstream inputStream;
			inputStream.open(input);
			string line;
			while (getline(inputStream, line))
			{
				fileText += line;
			}
			inputStream.close();
			return fileText;
		}
	}	
}
