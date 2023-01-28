#include <iostream>
#include <vector>

#include "login.h"
#include "blockChain.h"
#include "commandLoop.h"

int main()
{
    BlockChain blockChain = BlockChain();
    User currentUser = login();
    currentUser.calculateBalance(blockChain);

    commandLoop(blockChain, currentUser);

    return 1;
}