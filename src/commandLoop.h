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
            std::cout << "\n";
            user = User(false);
            user.calculateBalance(blockChain);
            std::cout << "\n";
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