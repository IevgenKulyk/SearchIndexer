#include "Indexer.h"


Indexer::Indexer()
{
}


Indexer::~Indexer()
{
}

void Indexer::InitFromLinearFile(std::string FilePath)
{
	FileParser parser;
	std::vector<std::string> words = parser.parseFile(FilePath);
	addWordsToIndexer(words,FilePath);
}

void Indexer::addWord(std::string word, const std::string& FilePath)
{
	try{
		std::set<std::string>& files = fastSearchAccess.at(word);
		files.insert(FilePath);
	}
	catch (std::out_of_range)
	{
		std::set<std::string> firstFile;
		firstFile.insert(FilePath);
		fastSearchAccess[word] = firstFile;
	}
}

void Indexer::addWordsToIndexer(const std::vector<std::string>& words,const std::string& FilePath)
{
	for (const std::string& word : words)
	{
		if (word.length())
			addWord(word, FilePath);
	}
}

std::string Indexer::SearchWordInFilesByIndexer(std::string word)
{
	std::string result;

	try{
		auto answer = fastSearchAccess.at(word);
		result = "Found in: ";
		for (auto x : answer)
		{
			result += x + ", ";
		}
		result = result.substr(0, result.length() - 2);
	}
	catch (std::out_of_range)
	{
		result = "No match found!";
	}

	return result;
}

void Indexer::replaceSpacesWithStars(std::string& FilePath)
{
	std::replace(FilePath.begin(), FilePath.end(), ' ', '*');
}

void Indexer::replaceStarsWithSpaces(std::string& FilePath)
{
	std::replace(FilePath.begin(), FilePath.end(), '*', ' ');
}

void Indexer::DumpIndexerToDisk(std::string IndexerFilePath)
{
	std::ofstream file(IndexerFilePath);
	for (auto entry : fastSearchAccess)
	{
		std::string outputLine = entry.first + " ";
		for (auto searchFile : entry.second)
		{
			std::string temp = searchFile;
			replaceSpacesWithStars(temp);
			outputLine += temp + ' ';
		}
		outputLine += "\n";
		file << outputLine;
	}
}

void Indexer::InitByIndexerDump(std::string FilePathOfDump)
{
	fastSearchAccess.clear();
	std::ifstream file(FilePathOfDump);

	std::string currentLine;
	while (std::getline(file, currentLine))
	{
		std::istringstream currentStream(currentLine);
		bool i = false;
		std::string theWord;
		
		while (currentStream)
		{
			std::string temp;
			currentStream >> temp;
			if (i == false)
			{
				theWord = temp;
				i = true;
			}
			else
			{
				std::string currentFile = temp;
				replaceStarsWithSpaces(currentFile);
				if (currentFile.length() > 1)
					addWord(theWord, currentFile);
			}			
		}
	}
}