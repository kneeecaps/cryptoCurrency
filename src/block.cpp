#include <iostream>
#include <thread>
#include <sstream>

#include "block.h"
#include "sha256.h"

Block::Block(std::string parsedData)
{
    _index = stoi(parsedData.substr(0, parsedData.find("<")));
    _nonce = stoi(parsedData.substr(parsedData.find("/") + 1, parsedData.find("*") - (parsedData.find("/") + 1)));

    std::string dataSubstr = parsedData.substr(parsedData.find("<") + 1, parsedData.find(">") - (parsedData.find("<") + 1));
    if(dataSubstr.length() > 0)
    {
        std::vector<std::string> transactionStrVec;
        std::string transactionStr;
        std::stringstream transactionSS(dataSubstr);

        while(std::getline(transactionSS, transactionStr, ':'))
        {
            transactionStrVec.push_back(transactionStr);
        }

        for(std::string transactionStr : transactionStrVec)
        {
            std::vector<std::string> transactionValues;
            std::string transactionValStr;
            std::stringstream transactionValSS(transactionStr);

            while(std::getline(transactionValSS, transactionValStr, ','))
            {
                transactionValues.push_back(transactionValStr);
            }

            std::string sender = transactionValues[0];
            std::string receiver = transactionValues[1];
            int amount = std::stoi(transactionValues[2]);

            Transaction transaction = Transaction(sender, receiver, amount);
            _data.push_back(transaction);
        }
    }

    _prevHash = parsedData.substr(parsedData.find(">") + 1, parsedData.find("/") - (parsedData.find(">") + 1));
    _hash = parsedData.substr(parsedData.find("*") + 1);

    _blockMined = true;
}
Block::Block(int index, std::vector<Transaction>& data, std::string prevHash, int difficulty)
{
    _index = index;
    _data = data;
    _prevHash = prevHash;

    unsigned int nThreads = std::thread::hardware_concurrency() / 2; //this is divided by two so the program doesn't hog all the available threads
    std::vector<std::thread> threads;

    for(int i = 0; i <= nThreads; i++)
    {
        std::thread miningThread(&Block::mineBlock, this, i, nThreads, difficulty);
        threads.push_back(std::move(miningThread));
    }
    for(int i = 0; i <= nThreads; i++)
    {
        threads[i].join();
    }
}

std::string Block::parseData(int exportFormat)
{
    std::stringstream blockDataSS;
    std::stringstream blockContentSS;

    for(Transaction transaction : _data)
    {
        blockContentSS << transaction.getSender() << "," << transaction.getReceiver() << "," << transaction.getAmount() << ":";
    }
    std::string blockContent = blockContentSS.str();
    if(!blockContent.empty())
    {
        blockContent.pop_back();
    }

    if(exportFormat == 0)
    {
        return blockContent;
    }
    else if(exportFormat > 0)
    {
        blockDataSS << _index << "<" << blockContent << ">" << _prevHash << "/" << _nonce;
    }
    if(exportFormat == 2)
    {
        blockDataSS << "*" << _hash;
    }

    std::string blockData = blockDataSS.str();
    return blockData;
}

void Block::mineBlock(int startNonce, int increment, int difficulty)
{
    std::stringstream blockContent;
    int nonce = startNonce;

    std::string prefix = std::string(difficulty, '0');

    std::string hash;

    while(hash.substr(0, difficulty) != prefix)
    {
        if(_blockMined)
        {
            break;
        }
        nonce += increment;
        blockContent = std::stringstream();
        blockContent << _index << "<" << parseData(0) << ">" << _prevHash << "/" << nonce;

        std::string blockContentStr = blockContent.str();

        hash = sha256(blockContentStr);
    }
    if(!_blockMined)
    {
        _nonce = nonce;
        _hash = hash;
        _blockMined = true;
        std::cout << "Index: " << _index << "\n";
        std::cout << "Content: " << blockContent.str() << "\n";
        std::cout << "Nonce: " << _nonce << "\n";
        std::cout << "Hash: " << _hash << "\n";
    }
}