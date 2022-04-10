#include "mineCommand.hpp"
#include "transactionCommand.hpp"

void commandLoop(blockChain& bChain)
{
  while(true)
  {
    std::string command;

    std::cout << "Command: ";
    getline(std::cin, command);

    if(command == "transaction")
    {
      transactionCommand(currentUser);
    }
    else if(command == "mine")
    {
      mineCommand(bChain);
    }
    else if(command == "userInfo")
    {
      std::cout << "Username: " << currentUser.username << "\n";
      std::cout << "Password hash: " << currentUser.password << "\n";
      std::cout << "Balance: " << currentUser.balance << "\n";
    }
    else if(command == "exit")
    {
      break;
    }
    else if(command == "switchUser")
    {
      login();
    }
    else if(command == "blockChain")
    {
      std::vector<block> blocks = bChain.getVChain();
      for(block& block : blocks)
      {
      std::cout << "\n";
      std::cout << "Block " << block.getIndex() << ":";
      std::cout << "\n";
      std::cout << "Nonce: " << block.getNonce();
      std::cout << "\n";
      std::cout << "Data: \n" << block.getData();
      std::cout << "\n";
      std::cout << "Hash: " << block.getHash();
      std::cout << "\n";
      std::cout << "Prev hash: " << block.getPrevHash();
      std::cout << "\n";
      }
    }
    else
    {
      std::cout << "\nThat is not a valid command.\n";
    }
  }
}
