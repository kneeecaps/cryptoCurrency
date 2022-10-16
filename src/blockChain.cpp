#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream> //just for debug, can remove later

#include "blockChain.h"

namespace fs = std::filesystem;

blockChain::blockChain() //constructor for blockChain
{
  _nDifficulty = 1; //change this number to make mining a block take longer, though the blockchain will be more secure
  //The lower the number, faster mining. The number is low for me because I wanted to test the mining algorithm, though recompiling after changing the number should work
}

std::vector<block> blockChain::getVChain() //function to get the blockChain
{
  return _vChain; //return the blockChain
}
int blockChain::getVChainLength() //function to get the length of the blockChain, used for getting the index of a new block
{
  return _vChain.size(); //return the size of the chain
}

block blockChain::_getLastBlock() const //return the last block, used for getting prevHash when making a new block
{
  return _vChain.back(); //return last block in the chain
}

void blockChain::addBlock(block bNew, bool mine) //function for adding a new block
{
  if(mine) //if the user wants to mine block, the block does not have to be mined in the importBChain function since we already have data which is why this is here
  {
    bNew.setPrevHash(_getLastBlock().getHash()); //set the block's prevHash field to the hash of the last block
    bNew.mineBlock(_nDifficulty); //function to mine the block, takes the difficulty (set in constructor of blockChain) as argument
  }
  _vChain.push_back(bNew); //add the new block to the blockchain
}

void blockChain::importBChain() //function to import the blockChain from the files it is stored in
{
  for(const auto& file : fs::directory_iterator("data/blocks/")) //loop through every file in the directory where the blockchain is stored
  { //the blocks in the chain are stored in individual files labelled by index, probably not very efficient but it works
    std::string fileName = file.path().filename().string(); //declare fileName variable and set it to the name of current file

    std::ifstream blockFile("data/blocks/" + fileName); //open the current file
    std::stringstream fileData; //declare a stringstream variable for the fileData

    char byte; //declare a variable for bytes
    while(blockFile.get(byte)) //for every character in the file
    {
      fileData << byte; //add the character into the stringstream
    } //I can't remember why I had to do this byte by byte, but it wasn't working without it for some reason

    std::string fileDataStr = fileData.str(); //turn the stringstream into a regular string

    //The file has its data stores between identifiers, the following code gets the data out from between these identifiers
    //these ints are the size, it is gotten by getting the position of the ending tag and subtracting the start tag
    //We can then get the data by taking a substring of the start tag through to the length of the data
    int nonceSize = fileDataStr.find(" :nonce!") - (fileDataStr.find("!nonce: ") + 8); //get the length of the nonce data
    int hashSize = fileDataStr.find(" :hash!") - (fileDataStr.find("!hash: ") + 7); //get the length of the hash data
    int prevHashSize = fileDataStr.find(" :prevHash!") - (fileDataStr.find("!prevHash: ") + 11); //get the length of the prevHash data

    std::string fBlockData = fileDataStr.substr(0, fileDataStr.find("~~~END DATA~~~")); //the block's data is equal to everything before its end tag
    int blockNonce = stoi(fileDataStr.substr(fileDataStr.find("!nonce: ") + 8, nonceSize)); //get the nonce and turn it into an integar
    std::string hash = fileDataStr.substr(fileDataStr.find("!hash: ") + 7, hashSize); //get the hash
    std::string prevHash = fileDataStr.substr(fileDataStr.find("!prevHash: ") + 11, prevHashSize); //get the prevHash

    block bNew(stoi(fileName), fBlockData, blockNonce, hash, prevHash); //create a new block object with the data gotten from the above code
    addBlock(bNew, false); //add this block, it does not need to be mined because we already have all the details (the nonce) mining would have gotten
  }
}
void blockChain::exportBChain() //function for saving the blockchain
{
  for(block& block : _vChain) //loop through every block in the blockChain
  {
    std::ofstream blockFile("data/blocks/" + std::to_string(block.getIndex())); //open the file for the block's index in write mode

    blockFile << block.getData() << "~~~END DATA~~~\n"; //write all the block's data into the file with the tags importBChain will use later
    blockFile << "!nonce: " << block.getNonce() << " :nonce!\n";
    blockFile << "!hash: " << block.getHash() << " :hash!\n";
    blockFile << "!prevHash: " << block.getPrevHash() << " :prevHash!\n";

    blockFile.close(); //close the file to save memory
  }
}

bool blockChain::verifyBChain() //function to verify that the chain has not been messed with
{
  std::string tmpHash; //define a temporary variable for the hash
  std::string oldTmpHash; //define another temporary variable but for the old hash
  for(block& block : _vChain) //loop through every block in the chain
  {
    if(block.getIndex() != 0) //if the block is not the original block
    {
      tmpHash = block.calculateHash(); //set tmpHash to the block's hash, this is caluclated right now so it can not be overriden by the file
      if(tmpHash != block.getHash()) //if the tmpHash does not equal the saved hash, we can be sure the block was tampered with
      {
        return false; //return false, meaning the chain is invalid
      }
      if(block.getIndex() != 1) //if the block is the first block with information, it won't have a previous hash so we can't do this test
      {
        if(block.getPrevHash() != oldTmpHash) //get the hash of the previous block and see if it is equal to oldTmpHash
        {
          return false; //if it isn't, we can be sure the block was tampered with and the chain is invalid
        }
      }
      oldTmpHash = tmpHash; //set oldTmpHash to the current hash. This means that in the next iteration, this will be the last block so we have the old hash stored
    }
  }
  return true; //if the program has not returned something yet, there is a high chance that the chain has not been tampered with
} //at some point, I might modify this code so it tries to repair the blockchain when someone messes with it, though this has not been done yet
