#include <iostream>

#include "blockChain.h"
#include "user.h"

#include "mineCommand.h"
#include "transactionCommand.h"

std::string upperCase(std::string input)
{
    std::string output;

    for(char i : input)
    {
        output += toupper(i);
    }
    return output;
}

void commandLoop(BlockChain& blockChain, User& user)
{
    std::string userInput;
    std::cout << "\n";

    while(true)
    {
        std::cout << "Command: ";
        std::getline(std::cin, userInput);
        userInput = upperCase(userInput);

        if(userInput == "MINE")
        {
            mineCommand(blockChain, user);
        }
        else if(userInput == "TRANSACTION")
        {
            transactionCommand(blockChain, user);
        }
        else if(userInput == "BLOCKCHAIN")
        {
            blockChain.showBChain();
        }
        else if(userInput == "USERINFO")
        {
            std::cout << "\nUsername: " << user.getUsername();
            std::cout << "\nPassword Hash: " << user.getPasswdHash();
            std::cout << "\nBalance: " << user.getBalance() << "\n\n";
        }
        else if(userInput == "SWITCHUSER")
        {
            std::string choice;

            std::cout << "Would you like to sign up (1) or sign in (2)?: ";
            std::getline(std::cin, choice);
            std::cout << "\n\n";

            if(choice == "1")
            {
                user = User(true);
            }
            else if(choice == "2")
            {
                user = User(false);
            }
            else
            {
                std::cout << "That is not a valid choice, please enter a valid choice.\n\n";
            }

            user.calculateBalance(blockChain);
        }
        else if(userInput == "EXIT")
        {
            break;
        }
        else
        {
            std::cout << "\nThat is not a valid command.\n\n";
        }
    }
}