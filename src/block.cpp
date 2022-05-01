#include <iostream>
#include <sstream>

#include "block.hpp"
#include "sha256.hpp"

block::block(int nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) //constructor, set the index and data of the block to the arguments
{
  _nNonce = -1; //set the nonce to -1, this is a starting point for the mining
}
block::block(int nIndexIn, const std::string &sDataIn, int nNonceIn, std::string sHashIn, std::string sPrevHashIn) : _nIndex(nIndexIn), _sData(sDataIn), _nNonce(nNonceIn), _sHash(sHashIn), _sPrevHash(sPrevHashIn) {}
//second constructor, this sets all of the arguments to the block's data instantly

int block::getIndex() //a heap of getter functions for the block's data
{
  return _nIndex;
}
int block::getNonce()
{
  return _nNonce;
}
std::string block::getData()
{
  return _sData;
}
std::string block::getHash()
{
  return _sHash;
}
std::string block::getPrevHash()
{
  return _sPrevHash;
}

void block::setPrevHash(std::string sPrevHashIn) //function that takes argument of a hash and sets the prevHash to this argument
{
  _sPrevHash = sPrevHashIn;
}

void block::mineBlock(int nDifficulty) //function to mine a block
{
  char *cstr = new char[nDifficulty + 1]; //code to get the identifier for a valid hash, cstr array that is the size of the difficulty

  for(int i = 0; i < nDifficulty; i++) //repeat until code has gone through every empty entry in the array
  {
    cstr[i] = '0'; //fill that entry in the array with a 0
  } //this code could be removed if you have a constant difficulty, but this makes it easier to change the difficulty

  cstr[nDifficulty] = '\0'; //add a terminating character to the end of the array

  std::string str(cstr); //turn that array into a string

  do //code to repeat until block is mined
  {
    _nNonce++; //increment (x + 1) the nonce
    _sHash = calculateHash(); //set the hash to calculate hash
  } while(_sHash.substr(0, nDifficulty) != str); //if the hash does not match the difficulty, repeat the above code

  std::cout << "Block mined: " << _sHash << "\n"; //if the code gets to here, the block has been mined. Tell the user this
}

std::string block::calculateHash() const //function to calculate the hash
{
  std::stringstream ss; //stringstream declared

  ss << _nIndex << _sData << _nNonce << _sPrevHash; //add all the data that needs to be in the block to the stringstream

  return sha256(ss.str()); //return sha256 of the string version of the stringstream
}
