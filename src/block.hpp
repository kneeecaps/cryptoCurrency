#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>

class block //define class for the blocks in the chain
{
private:
  int _nIndex; //variable for index of the block
  int _nNonce; //variable for nonce of the block
  std::string _sData; //variable for the block's data, the transactions
  std::string _sHash; //variable for the block's hash
  std::string _sPrevHash; //variable for the previous block's hash
public:
  block(int nIndexIn, const std::string &sDataIn); //constructor for when you are making a new block, only needs index and data and rest is mined
  block(int nIndexIn, const std::string &sDataIn, int nNonceIn, std::string sHashIn, std::string sPrevHashIn); //constructor for importing block, all information is known

  int getIndex(); //getter functions for the private variables
  int getNonce();
  std::string getData();
  std::string getHash();
  std::string getPrevHash();

  void setPrevHash(std::string sPrevHashIn); //setter function for the prev hash

  void mineBlock(int nDifficulty); //function to mine, takes difficulty as an argument
  std::string calculateHash() const; //function to calculate the block's hash
};

#endif
