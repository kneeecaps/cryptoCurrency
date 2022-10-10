#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void mineCommand(blockChain& bChain, user& currentUser) //mineCommand function, imported into commandLoop. Takes reference to blockChain as argument so it can be modified
{
  std::cout << "idk";
  std::vector<transaction> blockData; //defines vector of transactions which will be the data in the block
  std::stringstream blockTransactions; //defines string stream which the data from the vector will be switched to

  for (const auto& file : fs::directory_iterator("data/transactions")) //loop through ever file in the transactions directory
  { //this directory has stored all transactions not yet added to the blockchain
    std::string sender; //declare variable for the username of whoever is sended cryptocurrency
    std::string receiver; //declare variable for the username of whoever is receiving it
    std::string am; //declare variable for the tmp of the amount of cryptocurrency transfered
    int amount; //declare variable for the integar version of am variable

    std::string fileName = file.path().filename().string(); //declare a variable for the name of whatever file is currently selected by the loop

    std::ifstream transactionFile("data/transactions/" + fileName); //open the file selected by the loop

    std::cin.sync(); //this is just here because stackoverflow said it would fix cin taking weird input and it has worked so far
    getline(transactionFile, sender); //set the first line of the opened file to the sender variable
    getline(transactionFile, receiver); //set the second line of the opened file to the receiver variable
    getline(transactionFile, am); //set the third line of the opened file to the am variable

    amount = stoi(am); //set the amount variable to the integar version of the am variable

    transactionFile.close(); //free up memory by closing the file

    transaction readyTransaction(sender, receiver, amount); //create transaction object, this takes sender, receiver and amount as arguments

    int deleted = fs::remove("data/transactions/" + fileName); //delete the transaction file so the same transaction is not made multiple times
    //an issue with the above line of code is that it may make the output a bit dodgy if multiple users are mining at the same time
    //at this point, the code does not support multiple users logged in at the same time without multiple instances of all the files, so it isn't too bad right now

    blockData.push_back(readyTransaction); //add the transaction to the blockData vector to be used later
  }
  for(transaction& t : blockData) //for every transaction in the blockData vector
  {
    blockTransactions << t.sender << "\n" << t.receiver << "\n" << t.amount << "\n\n"; //add the data to the stringstream variable
  }
  std::string blockTransactionsStr = blockTransactions.str(); //turn the stringstream into a regular string
  bChain.addBlock(block(bChain.getVChainLength(), blockTransactionsStr), true); //add a block to the blockChain
  //the second argument for adding blocks is whether the block needs to be mined or not, this is mainly for debugging early versions of the code
  //it is mostly irrelevant now though I left it there just in case
  //the script for mining the block is part of the addBlock command and is not done in this file

  std::vector<block> blocks = bChain.getVChain(); //bellow code is just to display the whole blockchain
  for(block& block : blocks) //it is mostly there just because I needed to see the chain quickly after mining a block and it just saved some time
  {
    std::cout << "Block " << block.getIndex() << ":";
    std::cout << "\n";
    std::cout << "Nonce: " << block.getNonce();
    std::cout << "\n";
    std::cout << "Data: \n" << block.getData();
    std::cout << "\n";
    std::cout << "Hash: " << block.getHash();
    std::cout << "\n";
    std::cout << "Prev hash: " << block.getPrevHash();
    std::cout << "\n\n";
  }

  transaction blockPayment("blockChain", currentUser.username, 50); //create a transaction adding $50 to the user who mined the block as a reward
  user blockChain; //create a user to make the payout
  blockChain.username = "blockChain"; //give them a name, this is just for the records
  blockChain.balance = 50; //give them enough money to make the payout
  blockPayment.queueTransaction(blockChain); //queue the above transaction
  bChain.exportBChain(); //save the modified blockChain
  currentUser.findBalance(bChain); //recalculate the balance of the currentUser
}
