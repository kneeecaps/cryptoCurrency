#include <iostream>
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
}
Block::Block(int index, std::vector<Transaction>& data, std::string prevHash, int difficulty)
{
    _index = index;
    _data = data;
    _prevHash = prevHash;

    mineBlock(difficulty);
}

void Block::mineBlock(int& difficulty)
{
    std::stringstream blockDataSS;
    std::stringstream blockContent;
    int nonce = -1;

    for(Transaction transaction : _data)
    {
        blockDataSS << transaction.getSender() << "," << transaction.getReceiver() << "," << transaction.getAmount() << ":";
    }
    std::string blockData = blockDataSS.str();
    blockData.pop_back();

    std::string prefix = std::string(difficulty, '0');

    std::string hash;

    while(hash.substr(0, difficulty) != prefix)
    {
        nonce++;
        blockContent = std::stringstream();
        blockContent << _index << "<" << blockData << ">" << _prevHash << "/" << nonce;

        hash = sha256(blockContent.str());
        std::cout << hash << "\n";
    }
    _nonce = nonce;
    _hash = hash;
    std::cout << "Index: " << _index << "\n";
    std::cout << "Content: " << blockContent.str() << "\n";
    std::cout << "Nonce: " << _nonce << "\n";
    std::cout << "Hash: " << _hash << "\n";
}