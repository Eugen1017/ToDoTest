#include "auth.h"
#include <iostream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Auth::Auth(Database &db) : db(db) {
		std::string sql = "CREATE TABLE IF NOT EXISTS users ("
						  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
						  "username TEXT UNIQUE NOT NULL, "
						  "password TEXT NOT NULL);";

		db.execute(sql);
};

bool Auth::registerUser(const std::string &username, const std::string &password) {
	std::string hashed_password = hashPassword(password);
	std::string sql = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + hashed_password + "');";

	return db.execute(sql);
}

bool Auth::loginUser(const std::string &username, const std::string &password) {
	std::string hashed_password = hashPassword(password);
	std::string sql = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + hashed_password + "';";
	bool useer_found = false;

	auto callback = [](void *data, int argc, char **argv, char **azColName) -> int {
		bool *user_found = static_cast<bool *>(data);
		*user_found = true;
		return 0;
	};

	db.query(sql, callback, &useer_found);
	return useer_found;
}

std::string Auth::getCurrentUser() const {
	return currentUser;
}


std::string Auth::hashPassword(const std::string &password) {
	std::string salt = "random_salt";
	std::string salted_password = password + salt;

	unsigned char hash[SHA256_DIGEST_LENGTH];
	unsigned int hash_len;

	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	if (!mdctx) {
		throw std::runtime_error("Failed to create EVP_MD_CTX");
	}

	if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
		EVP_MD_CTX_free(mdctx);
		throw std::runtime_error("Failed to initialize SHA-256");
	}

	if (EVP_DigestUpdate(mdctx, salted_password.c_str(), salted_password.size()) != 1) {
		EVP_MD_CTX_free(mdctx);
		throw std::runtime_error("Failed to update SHA-256");
	}

	if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
		EVP_MD_CTX_free(mdctx);
		throw std::runtime_error("Failed to finalize SHA-256");
	}

	EVP_MD_CTX_free(mdctx);

	std::stringstream ss;
	for (unsigned int i = 0; i < hash_len; ++i) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(hash[i]);
	}

	return ss.str();
}
