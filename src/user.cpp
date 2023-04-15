#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "user.h"
#include "block.h"
#include "sha256.h"

char badCharacters[] = {':', ',', '/', '<', '>', '*'};

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
                    bool noBadChar = true;
                    for(char character : badCharacters)
                    {
                        if(username.find(character) != std::string::npos)
                        {
                            noBadChar = false;
                        }
                    }

                    if(noBadChar)
                    {
                        if(username != "blockChain")
                        {
                            newUsername = true;
                        }
                        else
                        {
                            std::cout << "\n\nYour username cannot be \"blockChain\".\n\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n\nThat username contains a character that is not allowed.";
                        std::cout << "\nMake sure your username does not contain any ':', ',', '/', '<', '> or '*'.\n\n";
                    }
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

void User::calculateBalance(BlockChain& blockChain)
{
    int usrBal = 0;

    for(Block block : blockChain.getBlockChain())
    {
        for(Transaction transaction : block.getData())
        {
            if(transaction.getSender() == _username)
            {
                usrBal -= transaction.getAmount();
            }
            if(transaction.getReceiver() == _username)
            {
                usrBal += transaction.getAmount();
            }
        }
    }

    std::vector<Transaction> pendingTransactions;
    std::vector<std::string> pendingTransactionStr;

    int fileCount = 0;
    for(auto& file : std::filesystem::directory_iterator("data/transactions"))
    {
        fileCount++;
    }
    for(int i = 0; i < fileCount; i++)
    {
        std::string filePath = "data/transactions/" + std::to_string(i);

        std::ifstream file(filePath);
        std::string fileStr;

        std::getline(file, fileStr);
        pendingTransactionStr.push_back(fileStr);

        file.close();
    }

    for(std::string tString : pendingTransactionStr)
    {
        std::vector<std::string> transactionValues;
        std::string transactionValStr;
        std::stringstream transactionValSS(tString);

        while(std::getline(transactionValSS, transactionValStr, ':'))
        {
            transactionValues.push_back(transactionValStr);
        }

        std::string sender = transactionValues[0];
        std::string receiver = transactionValues[1];
        int amount = stoi(transactionValues[2]);

        Transaction transaction = Transaction(sender, receiver, amount);

        pendingTransactions.push_back(transaction);
    }

    for(Transaction transaction : pendingTransactions)
    {
        if(transaction.getSender() == _username)
        {
            usrBal -= transaction.getAmount();
        }
    }

    _balance = usrBal;
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