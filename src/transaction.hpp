#include <string>

#include "user.hpp"

class transaction
{
public:
  std::string sender;
  std::string receiver;
  int amount;

  transaction(std::string sender, std::string reciever, int amount);

  bool verifyTransaction(user& currentUser);

  void queueTransaction();
  void makeTransaction();
};
