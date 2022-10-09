#ifndef USER_HPP
#define USER_HPP

#include "blockchain.hpp"

class user //user class
{
public: //this class was originally a struct, just made it an object so I can have the update function
  std::string username; //that is why these variables are public instead of private with getters and setters
  std::string password; //user class has variables for username, password and user balance
  int balance;

  void update(); //and a function for updating the file
  int findBalance(blockChain& bChain); //function for finding the balance of user
};

#endif
