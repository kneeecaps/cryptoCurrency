#include "mineCommand.h"
#include "transactionCommand.h"
#include "login.h"
#include "user.h"

void commandLoop(blockChain& bChain) //commandLoop function, imported into main. Takes reference to blockchain as argument so it can be modified
{
  user currentUser = login(bChain); //function to get user credentials and log the user into their account
  while(true) //this is here to keep looping through taking user input until the program is told to stop
  {
    std::string command; //defines a variable where what the user types will be stored

    std::cin.sync(); //idk why though this seems to fix the below lines taking weird input
    std::cout << "Command: "; //prompts user for the command
    getline(std::cin, command); //puts whatever the user typed into the variable defined before

    if(command == "transaction") //if the user typed transaction
    {
      transactionCommand(currentUser); //run the function for making a transaction
    }
    else if(command == "mine") //if the user typed mine
    {
      mineCommand(bChain, currentUser); //run the function for mining a block
    }
    else if(command == "userInfo") //if the user typed userInfo
    {
      std::cout << "Username: " << currentUser.username << "\n"; //return stored information about the currently signed in user
      std::cout << "Password hash: " << currentUser.password << "\n";
      std::cout << "Balance: " << currentUser.balance << "\n";
    }
    else if(command == "exit") //if the user typed exit
    {
      break; //exit the loop, causing the program to end after saving blockChain
    }
    else if(command == "switchUser") //if the user typed switchUser
    {
      currentUser = login(bChain); //runs login function again, to change stored user data
    }
    else if(command == "blockChain") //if the user typed blockChain
    { //this command shows all the stored information about the blockChain
      std::vector<block> blocks = bChain.getVChain(); //sets blocks to a vector of every block in the blockchain
      for(block& block : blocks) //loops through every element in the blocks vector
      {
      std::cout << "\n"; //cout information about the current block
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
    else //if the user typed something weird
    {
      std::cout << "\nThat is not a valid command.\n"; //tell user whatever they typed is not a command
    }
  }
}
