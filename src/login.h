#include <iostream>

#include "user.h"

void signUp()
{
    std::string username;

    std::cout << "Please enter a username: ";
    std::cin.ignore();
    std::getline(std::cin, username);

    User currentUser = User(username, true);
}
void signIn()
{
    std::cout << "signin";
}

void login()
{
    char choice;

    std::cout << "Would you like to sign up (1) or sign in (2)?: ";
    std::cin >> choice;
    std::cout << "\n\n";

    if(choice == '1')
    {
        signUp();
    }
    else if(choice == '2')
    {
        signIn();
    }
    else
    {
        std::cout << "That is not a valid choice, please enter a valid choice.\n\n";
        login();
    }
}