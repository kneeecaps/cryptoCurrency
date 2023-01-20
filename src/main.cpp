#include <iostream>

#include "login.h"

int main()
{
    User currentUser = login();
    std::cout << currentUser.getUsername() << "\n";
    std::cout << currentUser.getPasswdHash() << "\n";
    return 1;
}