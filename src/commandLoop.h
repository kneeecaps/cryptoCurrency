#include <iostream>

#include "blockChain.h"
#include "user.h"

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

    while(true)
    {
        std::cout << "Command: ";
        std::getline(std::cin, userInput);
        userInput = upperCase(userInput);

        if(userInput == "SHOWBLOCKCHAIN")
        {
            blockChain.showBChain();
        }
        else if(userInput == "EXIT")
        {
            break;
        }
        else
        {
            std::cout << "That is not a valid command.\n";
        }
    }
}