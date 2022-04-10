#include <iostream>
#include <sstream>

#include "block.hpp"
#include "sha256.hpp"

using namespace std;

block::block(int nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
  _nNonce = -1;
}
block::block(int nIndexIn, const std::string &sDataIn, int nNonceIn, std::string sHashIn, std::string sPrevHashIn) : _nIndex(nIndexIn), _sData(sDataIn), _nNonce(nNonceIn), _sHash(sHashIn), _sPrevHash(sPrevHashIn) {}

int block::getIndex()
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

void block::setPrevHash(std::string sPrevHashIn)
{
  _sPrevHash = sPrevHashIn;
}

void block::mineBlock(int nDifficulty)
{
  char *cstr = new char[nDifficulty + 1];

  for(int i = 0; i < nDifficulty; i++)
  {
    cstr[i] = '0';
  }

  cstr[nDifficulty] = '\0';

  std::string str(cstr);

  do
  {
    _nNonce++;
    _sHash = calculateHash();
  } while(_sHash.substr(0, nDifficulty) != str);

  std::cout << "Block mined: " << _sHash << "\n";
}

std::string block::calculateHash() const
{
  std::stringstream ss;

  ss << _nIndex << _sData << _nNonce << _sPrevHash;

  return sha256(ss.str());
}
