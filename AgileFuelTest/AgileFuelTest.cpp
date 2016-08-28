// AgileFuelTest.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include "Indexer.h"
#include <iostream>

int main(int argc, char* argv[])
{
	try{
		if (argc > 2)
		{
			std::string command = argv[1];
			if (command == "Index")
			{
				Indexer indexer;
				for (int i = 2; i < argc; i++)
					indexer.InitFromLinearFile(argv[i]);
				indexer.DumpIndexerToDisk("defaultIndexer.sqlite3");
			}
			else if (command == "Search" && argc > 3)
			{
				std::string advanced = argv[2];
				if (advanced == "Direct")
				{
					Indexer indexer;
					indexer.InitFromDump("defaultIndexer.sqlite3");
					for (int i = 3; i < argc; i++)
						std::cout << indexer.SearchWord(argv[i]) << std::endl;
				}
				//addditional features should be here
			}			
		}
	}
	catch (std::string& error)
	{
		std::cout << error << std::endl;
	}
	return 0;
}

