#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <vector>

#include "block.hpp"

class blockChain //defining the blockchain class
{
private:
  int _nDifficulty; //variable for the difficulty of mining, this is currently set in the constructor, though I might switch it to a config file at some point
  std::vector<block> _vChain; //variable for the actual block chain

  block _getLastBlock() const; //function for returning the last block
public:
  blockChain(); //constructor, this just sets the difficulty variable

  std::vector<block> getVChain(); //getter function for the blockchain
  int getVChainLength(); //function to get the length of the blockchain

  void addBlock(block bNew, bool mine); //function to add a block
  void importBChain(); //function to import the blockchain
  void exportBChain(); //function to save the blockchain
  bool verifyBChain(); //function to verify the blockchain
};

#endif
