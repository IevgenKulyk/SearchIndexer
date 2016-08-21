#pragma once

#include <string>
#include <set>
#include <map>
#include <algorithm>

#include "FileParser.h"

class Indexer
{
private:
	std::map<std::string, std::set<std::string>> fastSearchAccess;

public:
	Indexer();
	~Indexer();
	void InitFromLinearFile(std::string FilePath);
	std::string SearchWordInFilesByIndexer(std::string word);
	void DumpIndexerToDisk(std::string IndexerFilePath);
	void InitByIndexerDump(std::string FilePathOfDump);

private:
	void addWordsToIndexer(const std::vector<std::string>& words, const std::string& FilePath);
	void addWord(std::string word, const std::string& FilePath);
	void replaceSpacesWithStars(std::string& FilePath);
	void replaceStarsWithSpaces(std::string& FilePath);
};

