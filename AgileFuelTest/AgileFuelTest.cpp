// AgileFuelTest.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "Indexer.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::string command = argv[1];
		if (command == "Index")
		{
			Indexer indexer;
			for (int i = 2; i < argc; i++)
				indexer.InitFromLinearFile(argv[i]);
			indexer.DumpIndexerToDisk("defaultIndexer.txt");
		}
		else if (command == "Search")
		{
			Indexer indexer;
			indexer.InitByIndexerDump("defaultIndexer.txt");
			for (int i = 2; i < argc; i++)
				std::cout << indexer.SearchWordInFilesByIndexer(argv[i]) << std::endl;
		}
	}
	//Indexer indexer;
	//indexer.InitFromLinearFile("D:\\Crack\\books\\My Releases\\AgileFuelTest\\test1.txt");
	//std::cout << indexer.SearchWordInFilesByIndexer("hotel") << std::endl;
	//std::cout << indexer.SearchWordInFilesByIndexer("DemonHunterAlekseyGogogo") << std::endl;
	//indexer.DumpIndexerToDisk("D:\\Crack\\books\\My Releases\\AgileFuelTest\\indexer1.txt");
	//indexer.InitByIndexerDump("D:\\Crack\\books\\My Releases\\AgileFuelTest\\indexer1.txt");
	//std::cout << indexer.SearchWordInFilesByIndexer("hotel") << std::endl;
	//std::cout << indexer.SearchWordInFilesByIndexer("DemonHunterAlekseyGogogo") << std::endl;
	return 0;
}

