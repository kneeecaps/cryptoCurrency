#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

#include "user.hpp"

class transaction //declare class for transactions
{
public:
  std::string sender; //declare variables for the sender, receiver and amount. This was also originally a struct which is why these are public without getters and setters
  std::string receiver;
  int amount;

  transaction(std::string sender, std::string reciever, int amount); //constructor that takes the values and automatically assigns them
  transaction() {}; //empty constructor for when one isn't needed

  bool verifyTransaction(user& currentUser); //function to make sure the transaction is valid and no one is trying to cheat the system

  void queueTransaction(user& senderUser); //function to add the transaction to the list that will be mined with the next block
};

#endif
