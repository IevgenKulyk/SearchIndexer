#include "Database.h"

Database::Database()
{
}

sqlite3* Database::getHandle()
{
	return handle;
}

Database::Database(std::string& dbname)
{
	if (sqlite3_open(dbname.c_str(), &handle))
		throw std::string(sqlite3_errmsg(handle));
}

Database::~Database()
{
	sqlite3_close(handle);
}

void Database::SendRequest(std::string& request)
{
	char* error;
	if (SQLITE_OK != sqlite3_exec(handle, request.c_str(), NULL, 0, &error))
	{
		std::string errorMessage = error;
		sqlite3_free(error);
		throw errorMessage;
	}
}

void Database::createNewTable(std::string& TableName)
{
	sqlite3_stmt* statement;
	std::string sql = "CREATE TABLE IF NOT EXISTS \"";
	sql += TableName; //SQL injection possible
	sql += "\" (WORD TEXT,NUMBERINFILE INTEGER,OCCURENCES INTEGER);";

	if (sqlite3_prepare_v2(handle, sql.c_str(), -1, &statement, 0) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));	
	if (sqlite3_step(statement) != SQLITE_DONE)
		throw std::string(sqlite3_errmsg(handle));
	sqlite3_finalize(statement);
}

void Database::insertDataInTable(std::string& word, int number, std::string& TableName)
{
	sqlite3_stmt* statement;
	std::string sql = "INSERT INTO \"";
	sql += TableName; //SQL injection possible
	sql += "\" (WORD,NUMBERINFILE,OCCURENCES) VALUES (?,?,?);";
	if (sqlite3_prepare(handle, sql.c_str(), -1, &statement, 0) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));	
	if (sqlite3_bind_text(statement, 1, word.c_str(), word.length(), SQLITE_STATIC) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	if (sqlite3_bind_int(statement, 2, number) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	if (sqlite3_bind_int(statement, 3, 1) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	if (sqlite3_step(statement) != SQLITE_DONE)
		throw std::string(sqlite3_errmsg(handle));
	sqlite3_finalize(statement);	
}

std::string Database::Search(std::string& word,std::string& TableName)
{
	std::string result;
	sqlite3_stmt* statement;
	std::string sql = "SELECT * FROM \"";
	sql += TableName;
	sql += "\" WHERE WORD = ?;";
	if (sqlite3_prepare(handle, sql.c_str(), -1, &statement, 0) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	if (sqlite3_bind_text(statement, 1, word.c_str(), word.length(), SQLITE_STATIC) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	if (sqlite3_step(statement) == SQLITE_ROW)
		result = "found";
	sqlite3_finalize(statement);
	return result;
}

std::vector<std::string> Database::getAllTableNames()
{
	std::vector<std::string> result;
	sqlite3_stmt* statement;
	std::string sql = "SELECT name FROM sqlite_master WHERE type='table';";
	std::string Name;	
	unsigned char* tmp = NULL;

	if (sqlite3_prepare(handle, sql.c_str(), -1, &statement, 0) != SQLITE_OK)
		throw std::string(sqlite3_errmsg(handle));
	while (sqlite3_step(statement) == SQLITE_ROW)
	{
		int i = 0;
		while ((tmp = (unsigned char*)sqlite3_column_text(statement, i)) != NULL)
		{
			Name = reinterpret_cast<const char*> (sqlite3_column_text(statement, i++));
			result.push_back(Name);
		}
	}
	sqlite3_finalize(statement);

	return result;
}