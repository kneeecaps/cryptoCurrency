#include <iostream>
#include <string>

#include "blockChain.hpp"
#include "transaction.hpp"
#include "commandLoop.hpp"

//
//Parts of this code are very poorly written
//I am sure that at least half the code can be optimized a lot though I can not be bothered doing that at this point
//There are also really weird naming conventions used in this code. The files for the blockChain and block objects have a lot more detailed naming conventions
//On a lot of the other files, I dumbed down the names a bit and named them exactly what they are for.
//In the blockChain and block files, there are things such as an underscore before private variable names and the first letter of the type of variable in the name.
//At some point, I probably should standardize the variable names across the whole code, but it has not been done yet
//
//I also know that there are better ways to store the data than just plain text in files
//Having all the data stored in those text files is a bit easier than adding in support for something like json or an ms access database.
//I know that means the code is not as secure as it would be if I did something else, though this is more like a proof of concept
//Having a 100% secure blockchain is not really my goal here
//

int main()
{
  //need to change it so something is actually done when the block chain has been messed with instead of just putting it on screen then looping an error
  blockChain bChain; //declare blockchain object
  bChain.importBChain(); //import all the saved blocks into the block chain object
  if(bChain.verifyBChain()) //check if someone has tried to mess with the block chain
  {
    std::cout << "Block Chain Verified\n"; //if chain is good, tell user and continue
  }
  else
  {
    std::cout << "Block Chain broken/changed\n"; //if chain is bad, tell user, wait for input then close program
    system("pause");
    return 0;
  }

  commandLoop(bChain); //this just tells the program to start taking user input for what to do

  bChain.exportBChain(); //saves any modifications made to the blockchain to the files, at some point this might be moved to a destructor
  return 0;
}
