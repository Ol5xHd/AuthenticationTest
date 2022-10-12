#pragma once

#include "AuthModel.h"

class AuthView : public Observer {
public:
	AuthView(AuthModel* model);

	void update() override;
	void greetings();
	void status();
	void menu();
	void goodbye();
	void wrongInput();
	void enterName();
	void enterPasswd();
	void newUserRegistered();
	void userAlreadyExists();
	void userWasNotFoundByName();
	void userWasNotFoundByNameAndPasswd();
	void memoryInfo();
	void memoryInfoDetailed();
	void userWasDeleted();
	void noAccess();
	void listOfRegistered();

private:
	AuthModel* model;
};
