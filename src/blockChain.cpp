#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream> //just for debug, can remove later

#include "blockChain.hpp"

namespace fs = std::filesystem;

blockChain::blockChain()
{
  _nDifficulty = 1;
}

std::vector<block> blockChain::getVChain()
{
  return _vChain;
}
int blockChain::getVChainLength()
{
  return _vChain.size();
}

block blockChain::_getLastBlock() const
{
  return _vChain.back();
}

void blockChain::addBlock(block bNew, bool mine)
{
  if(mine)
  {
    bNew.setPrevHash(_getLastBlock().getHash());
    bNew.mineBlock(_nDifficulty);
  }
  _vChain.push_back(bNew);
}

void blockChain::importBChain()
{
  for(const auto& file : fs::directory_iterator("data\\blocks\\"))
  {
    std::string fileName = file.path().filename().string();

    std::ifstream blockFile("data\\blocks\\" + fileName);
    std::stringstream fileData;

    char byte;
    while(blockFile.get(byte))
    {
      fileData << byte;
    }

    std::string fileDataStr = fileData.str();

    int nonceSize = fileDataStr.find(" :nonce!") - (fileDataStr.find("!nonce: ") + 8);
    int hashSize = fileDataStr.find(" :hash!") - (fileDataStr.find("!hash: ") + 7);
    int prevHashSize = fileDataStr.find(" :prevHash!") - (fileDataStr.find("!prevHash: ") + 11);

    std::string fBlockData = fileDataStr.substr(0, fileDataStr.find("~~~END DATA~~~"));
    int blockNonce = stoi(fileDataStr.substr(fileDataStr.find("!nonce: ") + 8, nonceSize));
    std::string hash = fileDataStr.substr(fileDataStr.find("!hash: ") + 7, hashSize);
    std::string prevHash = fileDataStr.substr(fileDataStr.find("!prevHash: ") + 11, prevHashSize);

    block bNew(stoi(fileName), fBlockData, blockNonce, hash, prevHash);
    addBlock(bNew, false);
  }
}
void blockChain::exportBChain()
{
  for(block& block : _vChain)
  {
    std::ofstream blockFile("data\\blocks\\" + std::to_string(block.getIndex()));

    blockFile << block.getData() << "~~~END DATA~~~\n";
    blockFile << "!nonce: " << block.getNonce() << " :nonce!\n";
    blockFile << "!hash: " << block.getHash() << " :hash!\n";
    blockFile << "!prevHash: " << block.getPrevHash() << " :prevHash!\n";

    blockFile.close();
  }
}

bool blockChain::verifyBChain()
{
  std::string tmpHash;
  std::string oldTmpHash;
  for(block& block : _vChain)
  {
    if(block.getIndex() != 0)
    {
      tmpHash = block.calculateHash();
      if(tmpHash != block.getHash())
      {
        return false;
      }
      if(block.getIndex() != 1)
      {
        if(block.getPrevHash() != oldTmpHash)
        {
          return false;
        }
      }
      oldTmpHash = tmpHash;
    }
  }
  return true;
}
