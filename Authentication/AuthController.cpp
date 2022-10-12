#include "AuthController.h"
#include "AuthModel.h"

#include <iostream>
#include <sstream>

AuthController::AuthController(AuthModel* authModel, AuthView* authView)
{
    model = authModel;
    view = authView;
    waitForInput = false;
}

void AuthController::start()
{
    view->greetings();
    waitForInput = true;
    char buf[10];
    while (waitForInput) {
        view->status();
        view->menu();
        std::cin >> buf;
        switch (atoi(buf)) {
        case 1:
            registerUser();
            break;
        case 2:
            if (model->isAuthorized()) {
                deleteUser();
            }
            else {
                view->noAccess();
            }
            break;
        case 3:
            if (model->isAuthorized()) {
                logOut();
            }
            else {
                logIn();
            }
            break;
        case 4:
            if (model->isAuthorized()) {
                view->listOfRegistered();
            }
            else {
                view->noAccess();
            }
            break;
        case 5:
            view->memoryInfo();
            break;
        case 6:
            view->memoryInfoDetailed();
            break;
        case 7:
            waitForInput = false;
            view->goodbye();
            break;
        default:
            view->wrongInput();
        }
    }
}

void AuthController::registerUser() {
    char name[model_const::NAME_SIZE];
    char passwd[model_const::PASSWD_SIZE];
    view->enterName();
    std::cin >> name;
    view->enterPasswd();
    std::cin >> passwd;

    if (model->findUser(name)) {
        view->userAlreadyExists();
        return;
    }

    model->addUser(name, passwd);
    view->newUserRegistered();
}

void AuthController::logIn() {
    char name[model_const::NAME_SIZE];
    char passwd[model_const::PASSWD_SIZE];
    view->enterName();
    std::cin >> name;
    view->enterPasswd();
    std::cin >> passwd;

    if (model->findUser(name, passwd)) {
        model->setIsAuthorized(true);
    }
    else {
        view->userWasNotFoundByNameAndPasswd();
    }
}

void AuthController::logOut() {
    model->setIsAuthorized(false);
}

void AuthController::deleteUser() {
    char name[model_const::NAME_SIZE];
    view->enterName();
    std::cin >> name;

    if (model->deleteUser(name)) {
        view->userWasDeleted();
        return;
    }

    view->userWasNotFoundByName();
}
