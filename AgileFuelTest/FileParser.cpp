#include "FileParser.h"


FileParser::FileParser()
{
}


FileParser::~FileParser()
{
}

std::vector<std::pair<std::string, int>> FileParser::parseFile(std::string FilePath)
{
	std::vector<std::pair<std::string, int>> result;
	int number = 0;
	std::ifstream file(FilePath);

	std::string currentLine;
	while (std::getline(file, currentLine))
	{
		std::istringstream currentStream(currentLine);
		while (currentStream)
		{
			std::string temp;
			std::pair<std::string, int> element;
			currentStream >> temp;
			if (temp.length())
			{
				element.first = temp;
				element.second = number++;
				result.push_back(element);
			}
		}
	}

	return result;
}