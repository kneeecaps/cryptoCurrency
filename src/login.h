#include <iostream>

#include "user.h"

User login()
{
    std::string choice;
    User currentUser;

    std::cout << "Would you like to sign up (1) or sign in (2)?: ";
    std::getline(std::cin, choice);
    std::cout << "\n\n";

    if(choice == "1")
    {
        currentUser = User(true);
    }
    else if(choice == "2")
    {
        currentUser = User(false);
    }
    else
    {
        std::cout << "That is not a valid choice, please enter a valid choice.\n\n";
        login();
    }

    return currentUser;
}