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
    bool nextLoop = false;

    while(!userCreated)
    {
        nextLoop = false;

        if(newUser)
        {
            bool newUsername = false;
            bool pwMatch = false;

            while(!newUsername)
            {
                if(nextLoop)
                {
                    newUsername = true;
                    continue;
                }
                std::cout << "Please enter a username: ";
                std::getline(std::cin, username);

                std::ifstream userFile("data/users/" + username);
                if(!userFile.good())
                {
                    newUsername = true;
                }
                else
                {
                    std::string choice;
                    std::cout << "\n\nThat username is taken. Enter 1 to try logging in or 2 to try again.\n\n";
                    std::cout << "Choice: ";
                    std::getline(std::cin, choice);

                    if(choice == "1")
                    {
                        newUser = false;
                        nextLoop = true;
                    }
                }
            }

            while(!pwMatch)
            {
                if(nextLoop)
                {
                    pwMatch = true;
                    continue;
                }

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
                    std::string choice;
                    std::cout << "\n\nPasswords do not match. Enter 1 to try logging in or 2 to try again.\n";
                    std::cout << "Choice: ";
                    std::getline(std::cin, choice);

                    if(choice == "1")
                    {
                        newUser = false;
                        nextLoop = true;
                    }
                }
            }
            if(!nextLoop)
            {
                std::cout << "\nUser account successfully created.\n";

                std::ofstream userFile("data/users/" + username);
                userFile << passwdHash;
                userFile.close();    

                userCreated = true;
            }
        }
        else
        {
            bool goodUsername = false;
            bool rightPasswd = false;

            while(!goodUsername)
            {
                if(nextLoop)
                {
                    goodUsername = true;
                    continue;
                }

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
                        nextLoop = true;
                    }
                }
                userFile.close();
            }

            while(!rightPasswd)
            {
                if(nextLoop)
                {
                    rightPasswd = true;
                    continue;
                }

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
                        nextLoop = true;
                    }
                }
            }
            if(!nextLoop)
            {
                userCreated = true;
            }
        }
    }

    _username = username;
    _passwdHash = passwdHash;
}

void User::_calculateBalance()
{

}

bool User::userExists(std::string username)
{
    std::ifstream userFile("data/users/" + username);
    if(userFile.good())
    {
        userFile.close();
        return true;
    }
    else
    {
        userFile.close();
        return false;
    }
}