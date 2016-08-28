#pragma once

#include "sqlite3.h"

#include <string>
#include <vector>
#include <iostream>

class Database
{
private:
	sqlite3* handle;

	void SendRequest(std::string& request);
public:
	Database();
	Database(std::string& dbname);
	~Database();
	void createNewTable(std::string& TableName);
	void insertDataInTable(std::string& word,int number, std::string& TableName);
	std::string Search(std::string& word, std::string& TableName);
	sqlite3* getHandle();
	std::vector<std::string> getAllTableNames();
};

