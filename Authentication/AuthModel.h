#pragma once

#include <string.h>
#include <sstream>

#include "HeapManager.h"
#include "Observable.h"

namespace model_const {
	const size_t NAME_SIZE = 32;
	const size_t PASSWD_SIZE = 32;
} // namespace model_const

// struct for storing registered users
struct UserNode {
	UserNode(char* inName, char* inPasswd) {
		strcpy_s(name, inName);
		strcpy_s(passwd, inPasswd);
		next = nullptr;
	}

	char name[model_const::NAME_SIZE];
	char passwd[model_const::PASSWD_SIZE];
	UserNode* next;
};

class AuthModel : public Observable {
public:
	AuthModel(HeapManager* heapManagerObj);
	~AuthModel();

	// true, if user authorized
	bool isAuthorized() const;
	// change authorization state
	void setIsAuthorized(bool isAuthorized);
	// add new user to the list of registered
	void addUser(char* name, char* passwd);
	// try to find registered user by name
	bool findUser(char* name);
	// try to find registered user by name and password
	bool findUser(char* name, char* passwd);
	// delete user from registered by name
	bool deleteUser(char* name);
	// put all registered users into the stringstream
	void printAllUsers(std::stringstream& ss);
private:
	bool authorized;

	// simple and ineffective way to store registered users - but easy to control memory
	UserNode* usersHead;
};