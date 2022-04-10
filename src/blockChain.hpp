#include <vector>

#include "block.hpp"

class blockChain
{
private:
  int _nDifficulty;
  std::vector<block> _vChain;

  block _getLastBlock() const;
public:
  blockChain();

  std::vector<block> getVChain();
  int getVChainLength();

  void addBlock(block bNew, bool mine);
  void importBChain();
  void exportBChain();
  bool verifyBChain();
};
