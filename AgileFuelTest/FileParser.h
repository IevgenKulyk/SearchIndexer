#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class FileParser
{
public:
	FileParser();
	std::vector<std::pair<std::string, int>> parseFile(std::string);
	~FileParser();
};

