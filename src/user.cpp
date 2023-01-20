#include <iostream>
#include <fstream>

#include "user.h"
#include "sha256.h"

User::User(bool newUser)
{
    std::string username;
    std::string passwd;
    std::string cPasswd;
    std::string passwdHash;
    std::string cPasswdHash;
    std::string filePasswdHash;
    bool userCreated = false;

    while(!userCreated)
    {
        if(newUser)
        {
            bool newUsername = false;
            bool pwMatch = false;

            while(!newUsername)
            {
                std::cout << "Please enter a username: ";
                std::getline(std::cin, username);

                std::ifstream userFile("data/users/" + username);
                if(!userFile.good())
                {
                    newUsername = true;
                    _username = username;
                }
                else
                {
                    std::cout << "\n\nThis username is taken. Please try another one.\n\n";
                }
            }

            while(!pwMatch)
            {
                std::cout << "Please enter a password: ";
                std::getline(std::cin, passwd);
                std::cout << "Please confirm your password: ";
                std::getline(std::cin, cPasswd);

                passwdHash = sha256(passwd);
                cPasswdHash = sha256(cPasswd);

                if(passwdHash == cPasswdHash)
                {
                    pwMatch = true;
                }
                else
                {
                    std::cout << "\n\nPasswords did not match. Please try again.\n\n";
                }
            }
            std::cout << "\nUser account successfully created.\n";

            std::ofstream userFile("data/users/" + _username);
            userFile << passwdHash;
            userFile.close();    

            userCreated = true;   
        }
        else
        {
            bool goodUsername = false;
            bool rightPasswd = false;

            while(!goodUsername)
            {
                std::cout << "Please enter your username: ";
                std::getline(std::cin, username);

                std::ifstream userFile("data/users/" + username);
                if(userFile.good())
                {
                    goodUsername = true;
                }
                else
                {
                    std::string choice;
                    std::cout << "\n\nThat username does not exist. Enter 1 to create a new user or 2 to try again.\n";
                    std::cout << "Choice: ";
                    std::getline(std::cin, choice);

                    if(choice == "1")
                    {
                        newUser = true;
                    }
                }
                userFile.close();
            }

            while(!rightPasswd)
            {
                std::cout << "Please enter your password: ";
                std::getline(std::cin, passwd);

                passwdHash = sha256(passwd);

                std::ifstream userFile("data/users/" + username);
                std::getline(userFile, filePasswdHash);

                if(passwdHash == filePasswdHash)
                {
                    rightPasswd = true;
                }
                else
                {
                    std::string choice;
                    std::cout << "\n\nPassword is incorrect. Enter 1 to create a new account or 2 to try again.\n";
                    std::cout << "Choice: ";
                    std::getline(std::cin, choice);

                    if(choice == "1")
                    {
                        newUser = true;
                    }
                }
            }
            userCreated = true;
        }
    }

    _username = username;
    _passwdHash = passwdHash;
}

void User::_calculateBalance()
{

}