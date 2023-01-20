#include <iostream>
#include <vector>

#include "login.h"
#include "blockChain.h"
#include "block.h"

int main()
{
    BlockChain blockChain = BlockChain();
    User currentUser = login();

    std::vector<Transaction> tData;
    Transaction testTransaction1 = Transaction("Fred", "Carl", 5);
    tData.push_back(testTransaction1);
    Transaction testTransaction2 = Transaction("Carl", "Fred", 10);
    tData.push_back(testTransaction2);

    std::vector<Transaction> tData2;
    Transaction testTransaction3 = Transaction("Jeff", "Phil", 5);
    tData2.push_back(testTransaction3);
    Transaction testTransaction4 = Transaction("Phil", "Jeff", 10);
    tData2.push_back(testTransaction4);


    blockChain.addBlock(tData);
    blockChain.addBlock(tData2);

    blockChain.showBChain();

    return 1;
}