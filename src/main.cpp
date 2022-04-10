#include <iostream>
#include <string>

#include "blockChain.hpp"
#include "transaction.hpp"
#include "login.hpp"
#include "commandLoop.hpp"

int main()
{
  //need to change it so something is actually done when the block chain has been messed with instead of just putting it on screen then looping an error
  blockChain bChain;
  bChain.importBChain();
  if(bChain.verifyBChain())
  {
    std::cout << "Block Chain Verified\n";
  }
  else
  {
    std::cout << "Block Chain broken/changed\n";
    system("pause");
    return 0;
  }
  login();

  commandLoop(bChain);

  bChain.exportBChain();
  return 0;
}
