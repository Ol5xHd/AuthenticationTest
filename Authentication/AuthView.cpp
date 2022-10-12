#include "AuthView.h"

#include <iostream>
#include <sstream>

AuthView::AuthView(AuthModel* authModel) {
	model = authModel;
	model->addObserver(this);
}

void AuthView::update() {
	if (model->isAuthorized()) {
		std::cout << "Weclome, user!" << std::endl;
	}
	else {
		std::cout << "Goodbye, user!" << std::endl;
	}
}

void AuthView::greetings() {
	std::cout << "Hi! This is a demo authorization program." << std::endl;
}

void AuthView::status() {
	std::cout << std::endl;
	if (model->isAuthorized()) {
		std::cout << "You are FULLY authorized.";
	}
	else {
		std::cout << "You are NOT authorized.";
	}
	std::cout << std::endl;
}

void AuthView::menu() {
	std::stringstream ss;
	ss << "Please choose an option from 1 to 6 (input a number and push Enter)" << std::endl;
	ss << "1: Register new user." << std::endl;
	ss << "2: Delete registered user." << std::endl;
	if (model->isAuthorized()) {
		ss << "3. Log out." << std::endl;
	}
	else {
		ss << "3. Log in." << std::endl;
	}
	ss << "4: List of registered users." << std::endl;
	ss << "5: View short memory info." << std::endl;
	ss << "6: View detailed memory info." << std::endl;
	ss << "7: Exit program." << std::endl;
	std::cout << ss.str();
}

void AuthView::goodbye() {
	std::cout << "Great job! Goodbye!" << std::endl;
}

void AuthView::wrongInput() {
	std::cout << "Wrong input!" << std::endl;
}

void AuthView::enterName() {
	std::stringstream ss;
	ss << "Please enter user name (";
	ss << model_const::NAME_SIZE - 1;
	ss << " chars maximum): ";
	std::cout << ss.str();
}

void AuthView::enterPasswd() {
	std::stringstream ss;
	ss << "Please enter password (";
	ss << model_const::PASSWD_SIZE - 1;
	ss << " chars maximum): ";
	std::cout << ss.str();
}

void AuthView::newUserRegistered() {
	std::cout << "New user was successfully registered!" << std::endl;
}

void AuthView::userAlreadyExists() {
	std::cout << "Error - a user with the same name already exists!" << std::endl;
}

void AuthView::userWasNotFoundByName() {
	std::cout << "Error - a user with such name was not found!" << std::endl;
}

void AuthView::userWasNotFoundByNameAndPasswd() {
	std::cout << "Error - a user with such name and password was not found!" << std::endl;
}

void AuthView::memoryInfo() {
	HeapManager::getHeapManager()->printInfo();
}

void AuthView::memoryInfoDetailed() {
	HeapManager::getHeapManager()->printInfoDetailed();
}

void AuthView::userWasDeleted() {
	std::cout << "User was successfully deleted!" << std::endl;
}

void AuthView::noAccess() {
	std::cout << "You need to be authorized to perfom this action." << std::endl;
}

void AuthView::listOfRegistered() {
	std::stringstream ss;
	model->printAllUsers(ss);
	std::cout << "Registered:" << std::endl << ss.str();
}
