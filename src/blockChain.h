#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>

#include "block.h"
#include "transaction.h"

class BlockChain
{
private:
    std::vector<Block> _blockChain;
    const int _difficulty = 5;
    void _importBlockChain();
    void _exportBlockChain();
public:
    BlockChain();
    ~BlockChain();
    std::vector<Block> getBlockChain() {return _blockChain;}
    std::string getPrevHash() {return _blockChain.back().getHash();}

    void addBlock(std::vector<Transaction>& blockData);
    void showBChain();

    bool verifyBChain();
};

#endif