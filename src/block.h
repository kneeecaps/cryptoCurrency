#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "transaction.h"

class Block
{
private:
    int _index;
    int _nonce;
    std::vector<Transaction> _data;
    std::string _hash;
    std::string _prevHash;
    bool _blockMined = false;
public:
    Block(std::string parsedData);
    Block(int index, std::vector<Transaction>& data, std::string prevHash, int difficulty);

    int getIndex() {return _index;}
    int getNonce() {return _nonce;}
    std::vector<Transaction> getData() {return _data;}
    std::string getHash() {return _hash;}
    std::string getPrevHash() {return _prevHash;}

    std::string parseData(int exportFormat);

    void mineBlock(int startNonce, int increment, int difficulty);
};

#endif