#include "AuthModel.h"

AuthModel::AuthModel(HeapManager* heapManagerObj) :
	Observable(heapManagerObj), authorized(false), usersHead(nullptr) {}

AuthModel::~AuthModel() {
	UserNode* current = usersHead;
	while (current) {
		UserNode* toDelete = current;
		current = current->next;
		heapManager->deleteObject<UserNode>(toDelete);
	}
}

bool AuthModel::isAuthorized() const {
	return authorized;
}

void AuthModel::setIsAuthorized(bool isAuthorized) {
	authorized = isAuthorized;
	notifyUpdate();
}

void AuthModel::addUser(char* name, char* passwd) {
	UserNode* newNode = heapManager->createObject<UserNode>( name, passwd );
	
	if (!usersHead) {
		usersHead = newNode;
		return;
	}

	UserNode* current = usersHead;
	while (current->next) {
		current = current->next;
	}
	current->next = newNode;
}

bool AuthModel::findUser(char* name) {
	if (!usersHead) {
		return false;
	}

	UserNode* current = usersHead;
	while (current) {
		if (strcmp(current->name, name) == 0) {
			return true;
		}
		current = current->next;
	}

	return false;
}

bool AuthModel::findUser(char* name, char* passwd) {
	if (!usersHead) {
		return false;
	}

	UserNode* current = usersHead;
	while (current) {
		if (strcmp(current->name, name) == 0 && strcmp(current->passwd, passwd) == 0) {
			return true;
		}
		current = current->next;
	}

	return false;
}

bool AuthModel::deleteUser(char* name) {
	if (!usersHead) {
		return false;
	}

	UserNode* prev = nullptr;
	UserNode* current = usersHead;
	while (current) {
		if (strcmp(current->name, name) == 0) {
			if (prev) {
				prev->next = current->next;
			}
			else {
				usersHead = current->next;
			}
			heapManager->deleteObject<UserNode>(current);
			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

void AuthModel::printAllUsers(std::stringstream& ss) {
	UserNode* current = usersHead;
	while (current) {
		ss << current->name << std::endl;
		current = current->next;
	}
}
