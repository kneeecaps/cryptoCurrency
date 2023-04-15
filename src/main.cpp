#include "login.h"
#include "blockChain.h"
#include "commandLoop.h"

int main()
{
    BlockChain blockChain = BlockChain();
    if(!blockChain.verifyBChain()) {
        std::cout << "Blockchain is not valid. Please fix the issue, or delete all blocks after and including the problematic block.\n\n";
        return false;
    }
    std::cout << "\n\nBlockchain successfully verified.\n\n";

    User user = login();
    user.calculateBalance(blockChain);

    commandLoop(blockChain, user);

    return 1;
}