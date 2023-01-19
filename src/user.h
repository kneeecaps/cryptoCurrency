#IFNDEF USER_H
#DEFINE USER_H

#include <string>

class User
{
private:
    std::string _username;
    std::string _passwdHash;
    int _balance;
    void calculateBalance();
public:
    User(std::string username);
    User(std::string username, std::string passwdHash);

    std::string getUsername() {return _username;}
    std::string getPasswdHash() {return _passwdHash;}
    int getBalance() {return _balance;}
};

#ENDIF