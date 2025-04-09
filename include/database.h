#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
	Database(const std::string &db_name);
	~Database();
	bool execute(const std::string &sql);
	bool query(const std::string &sql, int (*callback)(void *, int, char **, char **), void *data);

private:
	sqlite3 *db;
};
#endif