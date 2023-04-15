#include <iostream>

#include "transaction.h"
#include "user.h"

void transactionCommand(BlockChain& blockChain, User& user)
{
    user.calculateBalance(blockChain);

    std::string receiver;
    std::string amountStr;
    int amount;
    std::string confirm;

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

    std::cout << "\nTransaction Summary: \n";
    std::cout << "Sender: " << newTransaction.getSender() << "\n";
    std::cout << "Receiver: " << newTransaction.getReceiver() << "\n";
    std::cout << "Amount: " << newTransaction.getAmount() << "\n";
    std::cout << "\nIs this right (y/n)? ";
    getline(std::cin, confirm);

    if(toupper(confirm[0]) == 'Y')
    {
        newTransaction.queueTransaction();
        std::cout << "\n\nThe transaction was recorded succesfully. The money has been deducted from your account now, but it will not be received until a block has been mined.";
    }
    else
    {
        std::cout << "\n\nThe transaction was not confirmed and therefore was not processed.";
    }
    std::cout << "\n\n";

    user.calculateBalance(blockChain);
}