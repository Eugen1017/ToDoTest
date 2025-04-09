#include "database.h"
#include <iostream>

Database::Database(const std::string &db_name) {
	if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
		std::cerr << "Can`t open database" << sqlite3_errmsg(db) << std::endl;
	}
}

Database::~Database() {
	sqlite3_close(db);
}

bool Database::execute(const std::string &sql) {
	char *errmsg = nullptr;

	if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errmsg << std::endl;
		sqlite3_free(errmsg);
		return false;
	}

	return true;
}

bool Database::query(const std::string &sql, int (*callback)(void *, int, char **, char **), void *data) {
	char *errmsg = nullptr;

	if (sqlite3_exec(db, sql.c_str(), callback, data, &errmsg) != SQLITE_OK) {
		std::cerr << "SQL error: " << errmsg << std::endl;
		sqlite3_free(errmsg);
		return false;
	}

	return true;
}