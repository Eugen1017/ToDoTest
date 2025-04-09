#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "database.h"

class Auth {
public:
	Auth(Database &db);
	bool loginUser(const std::string &username, const std::string &password);
	bool registerUser(const std::string &username, const std::string &password);
	std::string getCurrentUser() const;
	static std::string hashPassword(const std::string &password); // Додано метод для хешування пароля

private:
	Database &db;
	std::string currentUser; // Змінна для зберігання поточного користувача
};

#endif // AUTH_H