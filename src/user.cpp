#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "user.hpp"
#include "transaction.hpp"
#include "block.hpp"

void user::findBalance(blockChain& bChain) //function to find the balance of user
{
  std::vector<transaction> transactions; //vector for all the transactions
  int newBalance = 0; //integar for the new balance value

  for(block& block : bChain.getVChain()) //loop through every block in bChain
  {
    std::string data = block.getData(); //get the data out of the block
    if(data != "Genesis Block\n") //if the block isn't the first one
    {
      char newLine = '\n'; //set a char for the new line character
      int lines = std::count(data.begin(), data.end(), newLine); //count that character
      int currentLine = 1; //integar to store what line we are currently on
      int transactionCount = lines / 4; //integar to store expected amount of transactions
      int currentTransaction = 1; //integar to store what transaction we are on
      std::istringstream iss(data); //stackoverflow told me to use this to loop through lines
      transaction tmpTransaction; //declare temporary transaction
      
      for(std::string line; getline(iss, line);) //loop to go through each line
      {
        if(currentTransaction <= transactionCount) //if we haven't gone through all transactions
        {
          switch(currentLine) //switch statement for possibilities of currentLine
          {
            case 1: //if the current line should contain sender information
              tmpTransaction.sender = line; //set transaction sender to line
              break;
            case 2: //if current line should have receiver information
              tmpTransaction.receiver = line; //set receiver to line
              break;
            case 3: //if current line should have transaction amount
              tmpTransaction.amount = stoi(line); //set amount to the line
              break;
            case 4: //if new line between transactions
              currentLine = 0; //restart currentLine count
              currentTransaction++; //move currentTransaction to next one
              transactions.push_back(tmpTransaction); //add transaction to vector
              break;
          }
        }

        currentLine++; //increment currentLine variable for the next line
      }
    }
  }

  for(transaction currentTransaction : transactions) //loop through every transaction in vector
  {
    if(currentTransaction.sender == username) //if sent by currentUser
    {
      newBalance -= currentTransaction.amount; //subtract transaction amount
    }
    else if(currentTransaction.receiver == username) //if received by current user
    {
      newBalance += currentTransaction.amount; //add transaction amount
    }
    else
    {
      continue; //go to next iteration of loop if currentUser not in transaction
    }
  }

  balance = newBalance; //set balance to the new balance
}
