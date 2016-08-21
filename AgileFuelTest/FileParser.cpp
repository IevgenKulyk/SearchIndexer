#include "FileParser.h"


FileParser::FileParser()
{
}


FileParser::~FileParser()
{
}

std::vector<std::string> FileParser::parseFile(std::string FilePath)
{
	std::vector<std::string> result;
	std::ifstream file(FilePath);

	std::string currentLine;
	while (std::getline(file, currentLine))
	{
		std::istringstream currentStream(currentLine);
		while (currentStream)
		{
			std::string temp;
			currentStream >> temp;
			result.push_back(temp);
		}
	}

	return result;
}