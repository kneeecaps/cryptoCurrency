#include <iostream>
#include <vector>

#include "login.h"
#include "blockChain.h"

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
    Transaction testTransaction3 = Transaction("Jeff", "Phil", 20);
    tData2.push_back(testTransaction3);
    Transaction testTransaction4 = Transaction("Phil", "Jeff", 30);
    tData2.push_back(testTransaction4);

    std::vector<Transaction> tData3;
    Transaction testTransaction5 = Transaction("James", "Jim", 15);
    tData3.push_back(testTransaction5);
    Transaction testTransaction6 = Transaction("Jim", "James", 5);
    tData3.push_back(testTransaction6);


    blockChain.addBlock(tData);
    blockChain.addBlock(tData2);
    blockChain.addBlock(tData3);

    blockChain.showBChain();

    return 1;
}