#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "blockChain.h"
#include "sha256.h"

BlockChain::BlockChain()
{
    _importBlockChain();
}
BlockChain::~BlockChain()
{
    _exportBlockChain();
}

void BlockChain::addBlock(std::vector<Transaction>& blockData)
{
    Block newBlock = Block(_blockChain.size(), blockData, getPrevHash(), _difficulty);
    _blockChain.push_back(newBlock);

    _exportBlockChain();
}
void BlockChain::showBChain()
{
    std::cout << "\n\n";
    for(Block block : _blockChain)
    {
        std::cout << "Index: " << block.getIndex() << "\n";
        std::cout << "Nonce: " << block.getNonce() << "\n\n";
        std::cout << "Data: \n";
        for(Transaction transaction : block.getData())
        {
            std::cout << "Sender: " << transaction.getSender() << "\n";
            std::cout << "Receiver: " << transaction.getReceiver() << "\n";
            std::cout << "Amount: " << transaction.getAmount() << "\n\n";
        } 
        std::cout << "Hash: " << block.getHash() << "\n";
        std::cout << "Previous hash: " << block.getPrevHash() << "\n\n";
    }
}

void BlockChain::_importBlockChain()
{
    int fileCount = 0;
    for(auto& file : std::filesystem::directory_iterator("data/blockChain"))
    {
        fileCount++;
    }
    for(int i = 0; i < fileCount; i++)
    {
        std::ifstream file("data/blockChain/" + std::to_string(i));
        std::string blockContent;

        std::getline(file, blockContent);
        Block newBlock = Block(blockContent);
        _blockChain.push_back(newBlock);
    }
}
void BlockChain::_exportBlockChain()
{
    for(Block block : _blockChain)
    {
        std::string filePath = "data/blockChain/" + std::to_string(block.getIndex());
        std::ofstream blockFile(filePath);
        blockFile << block.parseData(2);
        blockFile.close();
    }
}

bool BlockChain::verifyBChain()
{
    std::string tmpPrevHash = "noHash";
    std::string blockHash;

    for(Block& block : _blockChain)
    {
        if(block.getIndex() == 0)
        {
            continue;
        }

        if(block.getPrevHash() != tmpPrevHash) {
            std::cout << "\n\nBlock " << block.getIndex() << " has an invalid prevHash.\n\n";
            return false;
        }
        tmpPrevHash = block.getHash();

        blockHash = sha256(block.parseData(1));
        if(block.getHash() != blockHash) {
            std::cout << "\n\nBlock " << block.getIndex() << " has an invalid hash.\n\n";
            return false;
        }
    }
    return true;
}