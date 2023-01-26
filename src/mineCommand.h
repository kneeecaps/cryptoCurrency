#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "blockChain.h"
#include "transaction.h"
#include "user.h"

std::vector<Transaction> getTransactions()
{
    std::vector<Transaction> transactions;
    std::vector<std::string> transactionStr;

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
        transactionStr.push_back(fileStr);

        file.close();
        std::filesystem::remove(filePath);
    }

    for(std::string tString : transactionStr)
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

        transactions.push_back(transaction);
    }
    return transactions;
}

void mineCommand(BlockChain& blockChain, User& user)
{
    std::vector<Transaction> data = getTransactions();
    blockChain.addBlock(data);

    Transaction rewardTransaction = Transaction("blockChain", user.getUsername(), 100);
    rewardTransaction.queueTransaction();
}