#include "Database.h"

Database& Database::getInstance()
{
	static Database instance; // Instantiated on first use.
	return instance;
}

Database::Database()
{
}

Database::~Database()
{
}