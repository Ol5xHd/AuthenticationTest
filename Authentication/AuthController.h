#pragma once

#include "AuthModel.h"
#include "AuthView.h"

class AuthController
{
public:
    AuthController(AuthModel* authModel, AuthView* authView);

    // main loop of all application
    void start();
    // add new user to model
    void registerUser();
    // delete registered user from model
    void deleteUser();
    // try to authorize
    void logIn();
    // unauthorize
    void logOut();

private:
    AuthModel* model;
    AuthView* view;

    bool waitForInput;
};