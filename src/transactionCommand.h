#include <iostream>

#include "transaction.h"
#include "user.h"

void transactionCommand(BlockChain& blockChain, User& user)
{
    std::string receiver;
    std::string amountStr;
    int amount;

    std::cout << "\nPlease enter the username of who you want to receive the money: ";
    getline(std::cin, receiver);

    if(!User::userExists(receiver))
    {
        std::cout << "\nThis user does not exist.\n\n";
        return;
    }

    std::cout << "\nPlease enter the amount for the transaction: ";
    getline(std::cin, amountStr);
    amount = stoi(amountStr);

    if(amount > user.getBalance())
    {
        std::cout << "\nYou do not have enough money to make this transaction.";
        std::cout << "\nYou have " << user.getBalance() << ", you need " << amount << ".\n\n";
        return;
    }

    Transaction newTransaction = Transaction(user.getUsername(), receiver, amount);
    newTransaction.queueTransaction();

    user.calculateBalance(blockChain);
}