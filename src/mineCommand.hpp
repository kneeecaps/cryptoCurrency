#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

void mineCommand(blockChain& bChain)
{
  std::vector<transaction> blockData;
  std::stringstream blockTransactions;

  for (const auto& file : fs::directory_iterator("data\\transactions"))
  {
    std::string sender;
    std::string receiver;
    std::string am;
    int amount;

    std::string fileName = file.path().filename().string();

    std::ifstream transactionFile("data\\transactions\\" + fileName);

    std::cin.sync();
    getline(transactionFile, sender);
    getline(transactionFile, receiver);
    getline(transactionFile, am);

    amount = stoi(am);

    transactionFile.close();

    transaction readyTransaction(sender, receiver, amount);

    readyTransaction.makeTransaction();

    int deleted = fs::remove("data\\transactions\\" + fileName);

    blockData.push_back(readyTransaction);
  }
  for(transaction& t : blockData)
  {
    blockTransactions << t.sender << "\n" << t.receiver << "\n" << t.amount << "\n\n";
  }
  std::string blockTransactionsStr = blockTransactions.str();
  bChain.addBlock(block(bChain.getVChainLength(), blockTransactionsStr), true);

  std::vector<block> blocks = bChain.getVChain();
  for(block& block : blocks)
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

  transaction blockPayment("blockChain", currentUser.username, 50);
  blockPayment.queueTransaction();
  bChain.exportBChain();
}
