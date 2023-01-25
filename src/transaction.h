#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>

class Transaction
{
private:
    std::string _sender;
    std::string _receiver;
    int _amount;
public:
    Transaction(std::string sender, std::string receiver, int amount);

    std::string getSender() {return _sender;}
    std::string getReceiver() {return _receiver;}
    int getAmount() {return _amount;}

    void queueTransaction();
};

#endif