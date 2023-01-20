#include "transaction.h"

Transaction::Transaction(std::string sender, std::string receiver, int amount)
{
    _sender = sender;
    _receiver = receiver;
    _amount = amount;
}
