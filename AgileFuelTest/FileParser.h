#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class FileParser
{
public:
	FileParser();
	std::vector<std::string> parseFile(std::string);
	~FileParser();
};

