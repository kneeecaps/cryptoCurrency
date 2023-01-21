#include <iostream>
#include <thread>
#include <sstream>

#include "block.h"
#include "sha256.h"

Block::Block(int index, int nonce, std::vector<Transaction>& data, std::string hash, std::string prevHash)
{
    _index = index;
    _nonce = nonce;
    _data = data;
    _hash = hash;
    _prevHash = prevHash;
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

std::string Block::parseData(bool exportFormat)
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

    if(exportFormat)
    {
        return blockContent;
    }
    else
    {
        blockDataSS << _index << "<" << blockContent << ">" << _prevHash << "/" << _nonce;
        std::string blockData = blockDataSS.str();

        return blockData;
    }
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
        blockContent << _index << "<" << parseData(false) << ">" << _prevHash << "/" << nonce;

        hash = sha256(blockContent.str());
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