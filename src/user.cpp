#include <fstream>
#include <iostream> //only here for debug, remove later
#include <vector>

#include "user.hpp"
#include "transaction.hpp"
#include "block.hpp"

void user::update() //one function, to update the user's file with whatever values are stored in the object
{
  std::ofstream userFile("data/users/" + username); //open the file

  userFile << username << "\n" << password << "\n"; //write whatevers in the object to the file

  userFile.close(); //close the file to save memory
}

int user::findBalance(blockChain& bChain) //function to find the balance of user
{
  std::vector<transaction> transactions;
  std::vector<std::string> rawTransactions;
  int balance;

  for(block& block : bChain.getVChain())
  {
    std::string data = block.getData();
    std::cout << data;
  }

  //return balance;
}
