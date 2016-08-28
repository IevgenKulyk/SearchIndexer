#include "Indexer.h"

Indexer::Indexer()
{
	db = new Database(std::string(":memory:"));
}

Indexer::~Indexer()
{
	delete db;
}

void Indexer::InitFromLinearFile(std::string FilePath)
{	
	db ->createNewTable(FilePath);

	FileParser parser;
	std::vector<std::pair<std::string, int>> words = parser.parseFile(FilePath);
	for (auto element : words)
	{
		db->insertDataInTable(element.first, element.second, FilePath);
	}
}

void Indexer::DumpIndexerToDisk(std::string IndexerFilePath)
{
	sqlite3* dump;
	remove(IndexerFilePath.c_str());	
	if (sqlite3_open(IndexerFilePath.c_str(), &dump))
		throw std::string("Unable to dump to disk");

	sqlite3_backup *pBackup = sqlite3_backup_init(dump, "main", db ->getHandle(), "main");
	sqlite3_backup_step(pBackup, -1);
	sqlite3_backup_finish(pBackup);
	sqlite3_close(dump);
}

void Indexer::InitFromDump(std::string DumpName)
{
	sqlite3* dump;
	
	if (sqlite3_open(DumpName.c_str(), &dump))
		throw std::string("Unable to read dump");

	sqlite3_backup *pBackup = sqlite3_backup_init(db->getHandle(), "main", dump , "main");
	sqlite3_backup_step(pBackup, -1);
	sqlite3_backup_finish(pBackup);
	sqlite3_close(dump);
}

std::string Indexer::SearchWord(std::string word)
{
	std::string result = word + " Found at: ";
	unsigned int empty = result.length();
	std::vector<std::string> TableNames = db->getAllTableNames();
	for (auto Name : TableNames)
	{
		if (db->Search(word, Name) == "found")
		{
			result += Name + " ";
		}		
	}
	if (result.length() == empty)
		result = "No matches found!";
	return result;
}
