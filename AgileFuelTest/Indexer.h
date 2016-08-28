#pragma once

#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>

#include "FileParser.h"
#include "Database.h"

class Indexer
{
private:
	Database* db;

public:
	Indexer();
	~Indexer();
	void InitFromLinearFile(std::string FilePath);
	std::string SearchWord(std::string word);
	void DumpIndexerToDisk(std::string IndexerFilePath);	
	void InitFromDump(std::string DumpName);
};

