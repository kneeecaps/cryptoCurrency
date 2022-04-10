#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "transaction.hpp"
#include "sha256.hpp"

namespace fs = std::filesystem;

transaction::transaction(std::string sender, std::string reciever, int amount) : sender(sender), receiver(reciever), amount(amount) {}

bool transaction::verifyTransaction(user& currentUser)
{
  std::ifstream receiverFileTest("data\\users\\" + receiver);
  if(receiverFileTest.good())
  {
    if(currentUser.balance > amount)
    {
      receiverFileTest.close();
      return true;
    }
    else
    {
      std::cout << "\n\nYou don't have enough coins\n";
      receiverFileTest.close();
      return false;
    }
  }
  else
  {
    std::cout << "\n\nReceiver does not exist";
    receiverFileTest.close();
    return false;
  }
}
void transaction::queueTransaction()
{
  std::string sUsername;
  std::string sPassword;
  std::string sBal;
  int sBalance;

  user senderUser;

  std::ifstream senderReadFile("data\\users\\" + sender);

  std::cin.sync();
  getline(senderReadFile, sUsername);
  getline(senderReadFile, sPassword);
  getline(senderReadFile, sBal);


  sBalance = stoi(sBal);

  senderReadFile.close();

  senderUser.username = sUsername;
  senderUser.password = sPassword;
  senderUser.balance = sBalance;

  if(senderUser.username != "blockChain")
  {
    senderUser.balance = senderUser.balance - amount;
  }

  senderUser.update();

  std::stringstream ss;
  ss << sender << receiver << amount;

  bool fileMade = false;
  int fileAttempts = 0;
  std::string transactionFileName;

  while(!fileMade)
  {
    std::string temp;
    std::string fileAttemptsStr = std::to_string(fileAttempts);

    if(fs::exists("data\\transactions\\" + sha256(ss.str()) + fileAttemptsStr)) //for some reason this makes x+1 transaction files for the miner payment. Probably should fix that
    {
      fileAttempts++;
    }
    else
    {
      fileMade = true;
      transactionFileName = "data\\transactions\\" + sha256(ss.str()) + fileAttemptsStr;
    }
  }

  std::ofstream transactionFile(transactionFileName);
  transactionFile << sender << "\n" << receiver << "\n" << amount;
  transactionFile.close();
}
void transaction::makeTransaction()
{
  user receiverUser;

  std::string rUsername;
  std::string rPassword;
  std::string rBal;
  int rBalance;

  std::ifstream receiverReadFile("data\\users\\" + receiver);

  std::cin.sync();
  getline(receiverReadFile, rUsername);
  getline(receiverReadFile, rPassword);
  getline(receiverReadFile, rBal);

  rBalance = stoi(rBal);

  receiverReadFile.close();

  receiverUser.username = rUsername;
  receiverUser.password = rPassword;
  receiverUser.balance = rBalance + amount;

  receiverUser.update();
}
