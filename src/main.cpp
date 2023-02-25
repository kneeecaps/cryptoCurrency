#include "login.h"
#include "blockChain.h"
#include "commandLoop.h"

int main()
{
    BlockChain blockChain = BlockChain();
    User user = login();
    user.calculateBalance(blockChain);

    commandLoop(blockChain, user);

    return 1;
}