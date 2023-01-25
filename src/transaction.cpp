#include <filesystem>
#include <fstream>

#include "transaction.h"

Transaction::Transaction(std::string sender, std::string receiver, int amount)
{
    _sender = sender;
    _receiver = receiver;
    _amount = amount;
}

void Transaction::queueTransaction()
{
    int fileCount = 0;
    for(auto& file : std::filesystem::directory_iterator("data/transactions"))
    {
        fileCount++;
    }
    std::ofstream file("data/transactions/" + std::to_string(fileCount));
    file << _sender << ":" << _receiver << ":" << std::to_string(_amount);
    file.close();
}