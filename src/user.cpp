#include <iostream>

#include "user.h"

User::User(std::string username)
{
    std::string passwd;
    std::string cPasswd;

    bool pwMatch = false;
    while(!pwMatch)
    {
        std::cout << "Please enter a password: ";
        std::cin.ignore();
        std::getline(std::cin, passwd);
        std::cout << "Please confirm your password: ";
        std::cin.ignore();
        std::getline(std::cin, cPasswd);

        if(passwd == cPasswd)
        {
            pwMatch = true;
        }
        else
        {
            std::cout << "\n\nPasswords did not match. Please try again.\n\n";
        }
    }
    std::cout << "Password successfully set.\n";
    
    //hash password and save it in file now.
}
User::User(std::string username, std::string passwdHash)
{

}

void User::calculateBalance()
{

}