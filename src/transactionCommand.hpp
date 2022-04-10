void transactionCommand(user& currentUser)
{
  std::string name;
  std::string receiver;
  int amount;
  char confirm;

  std::cout << "Receiver name: ";
  getline(std::cin, receiver);
  std::cout << "Amount: ";
  std::cin >> amount;

  transaction newTransaction(currentUser.username, receiver, amount);

  std::cout << "\n\n";
  std::cout << "Sender: " << newTransaction.sender << "\n";
  std::cout << "Reciever: " << newTransaction.receiver << "\n";
  std::cout << "Amount: " << newTransaction.amount << "\n";

  if(newTransaction.verifyTransaction(currentUser))
  {
    std::cout << "\n\nConfirm? (Y/N): ";
    std::cin >> confirm;
    if(confirm == 'Y' || confirm == 'y')
    {
      newTransaction.queueTransaction();
    }
  }
  else
  {
    std::cout << "Error: Could not make transaction";
  }
}
