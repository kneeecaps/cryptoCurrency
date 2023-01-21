#include <iostream>
#include <sstream>
#include <fstream>

#include "blockChain.h"

BlockChain::BlockChain()
{
    std::vector<Transaction> tData;
    Block firstBlock = Block(0, 0, tData, "noHash", "noHash");
    _blockChain.push_back(firstBlock);
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

}
void BlockChain::_exportBlockChain()
{
    for(Block block : _blockChain)
    {
        std::stringstream blockDataSS;

        for(Transaction transaction : block.getData())
        {
            blockDataSS << transaction.getSender() << "," << transaction.getReceiver() << "," << transaction.getAmount() << ":";
        }
        std::string blockData = blockDataSS.str();
        //std::cout << blockData;
        if(!blockData.empty())
        {
            blockData.pop_back();
        }

        std::stringstream fileDataSS;
        fileDataSS << block.getIndex() << "<" << blockData << ">" << block.getPrevHash() << "/" << block.getNonce();
        std::string fileData = fileDataSS.str();
        std::cout << fileData << "\n";

        std::string filePath = "data/blockChain/" + std::to_string(block.getIndex());
        std::ofstream blockFile(filePath);
        blockFile << fileData;
        blockFile.close();
    }
}