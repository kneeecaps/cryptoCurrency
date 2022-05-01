void transactionCommand(user& currentUser) //transactionCommand function, imported into commandLoop. Takes reference to blockChain as argument so it can be modified
{
  std::string receiver; //declare a variable for the username of who is going to receive the money
  int amount; //declare a variable for the amount of cryptocurrency being transfered
  char confirm; //declare a variable being used to confirm the transaction

  std::cout << "Receiver name: "; //prompt the user for the receiver name
  getline(std::cin, receiver); //set whatever they typed to the receiver variable
  std::cout << "Amount: "; //prompt the user for the amount to be transfered
  std::cin >> amount; //set whatever they typed to the amount variable

  transaction newTransaction(currentUser.username, receiver, amount); //create the transaction object with the currently signed in user, receiver and the amount

  std::cout << "\n\n"; //create some line breaks to organize output better
  std::cout << "Sender: " << newTransaction.sender << "\n"; //relay back to the user the details of the created transaction
  std::cout << "Reciever: " << newTransaction.receiver << "\n";
  std::cout << "Amount: " << newTransaction.amount << "\n";

  if(newTransaction.verifyTransaction(currentUser)) //verify the transaction, mainly by checking if the sender can actually afford to send the money
  {
    std::cout << "\n\nConfirm? (Y/N): "; //make sure the user is happy with the inputs they have given the system
    std::cin >> confirm; //confirm variable to tell if user is happy or not with their inputs
    if(confirm == 'Y' || confirm == 'y') //if they said yes, code also makes sure the required input is not case sensitive
    {
      newTransaction.queueTransaction(currentUser); //make the transaction
    }
  }
  else
  {
    std::cout << "Error: Could not make transaction"; //if anything goes wrong, like sender can't afford it or receiver doesn't exist, tell user transaction was not made.
    //at some point I could make the error message more specific to exactly why the transaction was not made but I can't be bothered doing that now
  }
}
