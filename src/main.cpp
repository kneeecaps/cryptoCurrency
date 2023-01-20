#include <iostream>
#include <vector>

#include "login.h"
#include "block.h"

int main()
{
    User currentUser = login();

    std::vector<Transaction> tData;
    Transaction testTransaction1 = Transaction("Fred", "Carl", 5);
    tData.push_back(testTransaction1);
    Transaction testTransaction2 = Transaction("Carl", "Fred", 10);
    tData.push_back(testTransaction2);

    int difficulty = 3;
    Block block = Block(0, tData, difficulty);

    return 1;
}