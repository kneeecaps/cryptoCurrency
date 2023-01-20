#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    std::string _username;
    std::string _passwdHash;
    int _balance;
    void _calculateBalance();
public:
    User(bool newUser);
    User(){}

    std::string getUsername() {return _username;}
    std::string getPasswdHash() {return _passwdHash;}
    int getBalance() {return _balance;}
};

#endif