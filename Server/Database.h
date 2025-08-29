#pragma once

class Database
{
public:
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database& getInstance();

private:
	Database();
	~Database();
};

