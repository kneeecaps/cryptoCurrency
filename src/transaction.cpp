#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "transaction.hpp"
#include "sha256.hpp"

namespace fs = std::filesystem;

transaction::transaction(std::string sender, std::string reciever, int amount) : sender(sender), receiver(reciever), amount(amount) {}
//constructor that just defines all the variables in the class to what is in the arguments

bool transaction::verifyTransaction(user& currentUser) //function to make sure the transaction is valid
{
  std::ifstream receiverFileTest("data\\users\\" + receiver); //open the file for the account of the receiver
  if(receiverFileTest.good()) //if the file is there, account exists
  {
    if(currentUser.balance > amount) //check if the current user can afford to make the transaction
    {
      receiverFileTest.close(); //close the file, we don't need it anymore
      return true; //return true, transaction should be vaid
    }
    else //if user can't afford to make the transaction
    {
      std::cout << "\n\nYou don't have enough coins\n"; //tell the user they can't afford it
      receiverFileTest.close(); //we don't need the file anymore so close it
      return false; //return false, transaction is not valid
    }
  }
  else //if the receiver's account file can't be opened, if it does not exist
  {
    std::cout << "\n\nReceiver does not exist"; //tell the user this
    receiverFileTest.close(); //close the file
    return false; //return false, transaction is invalid
  }
}
void transaction::queueTransaction(user& senderUser) //function for the user that is sending the cryptocurrency
{
  if(senderUser.username != "blockChain") //if the username of the user is not blockchain
  { //the blockchain is a default account that is used to payout rewards for miners, this is here so it does not run out of money
    senderUser.balance = senderUser.balance - amount; //decrease the balance of the user if they are not the blockchain
    senderUser.update(); //call the update function for the user to save their new balance in their file
  }

  std::stringstream ss; //declare a stringstream
  ss << sender << receiver << amount; //set the stringstream to the sender, receiver and amount of the transaction

  bool fileMade = false; //bool for if the file for the transaction has been made
  int fileAttempts = 0; //number of attempts to make the transaction file, should be 0 at this point in the code
  std::string transactionFileName; //string for the file name

  while(!fileMade) //while the file has not been made
  {
    std::string temp; //create tmp string
    std::string fileAttemptsStr = std::to_string(fileAttempts); //turn the fileAttempts int to a string

    if(fs::exists("data\\transactions\\" + sha256(ss.str()) + fileAttemptsStr)) //if the file exists
    {//the sha256 of the data + a number for attempts is a code for the file name. The number is just there so the same transaction (which will have the same sha)
      fileAttempts++; //can be made multiple times. If the file is there, we will increment the attempts then try again with a one higher number until it works
    }
    else //if the file has not been made
    {
      fileMade = true; //set fileMade to true to break out of the loop
      transactionFileName = "data\\transactions\\" + sha256(ss.str()) + fileAttemptsStr; //set the file name to whatever worked when the loop was broken
    }
  }

  std::ofstream transactionFile(transactionFileName); //create a file by the filename that the above code said works
  transactionFile << sender << "\n" << receiver << "\n" << amount; //put the data into this file
  transactionFile.close(); //close the file, we are done with it.
}
void transaction::makeTransaction(user& currentUser) //function to making the transactions, used when mining blocks
{
  user receiverUser; //create a user for whoever is going to be receiving the money

  std::string rUsername; //define variables for the data of this user
  std::string rPassword;
  std::string rBal;
  int rBalance;

  std::ifstream receiverReadFile("data\\users\\" + receiver); //open the user's file, we know it will work because this transaction will have already been verified

  std::cin.sync(); //this just makes the getline functions run a bit better and with less potential for bugs
  getline(receiverReadFile, rUsername); //read the data from the receiver's file
  getline(receiverReadFile, rPassword);
  getline(receiverReadFile, rBal);

  rBalance = stoi(rBal); //turn the string version of the data to an integar

  receiverReadFile.close(); //close the file, we don't need it anymore

  receiverUser.username = rUsername; //set the receiver user's data to their username and password
  receiverUser.password = rPassword;
  receiverUser.balance = rBalance + amount; //their balance will equal their current balance + the transaction amount

  receiverUser.update(); //save this new data to their file

  if (receiverUser.username == currentUser.username) //if the receiver is the current logged in user
  {
    currentUser.balance = rBalance + amount; //update their balance in runtime as well as their file
  }
}
