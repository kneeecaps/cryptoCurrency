#include <iostream>
#include <fstream>
#include <string>

#include "user.hpp"
#include "sha256.hpp"

user login() //function to log in, it returns a logged in user
{
  int choice; //something to store whether the user wants to register or log in
  user currentUser; //a variable to store the user

  std::cout << "1: Register\n2: Login\nYour choice: "; //ask user if they want to log in or register
  std::cin >> choice; //store their decision

  if(choice == 1) //if the user wants to register
  {
    std::string username, password, confirmPassword; //declare variables for their username, their password and to confirm the password

    std::cin.sync(); //this is just here because there is sometimes weird inputs without it
    std::cout << "Select a username: "; //prompt user for their username
    getline(std::cin, username); //take their input
    std::cout << "Select a password: "; //prompt user for their password
    getline(std::cin, password); //take their input
    password = sha256(password); //immediately hash the password they put in
    std::cout << "Confirm password: "; //prompt user to confirm their password
    getline(std::cin, confirmPassword); //take their input
    confirmPassword = sha256(confirmPassword); //immediately hash the confirmed password

    if (password != confirmPassword) //if the passwords do not match
    {
      std::cout << "Password did not match!\n"; //tell the user that they didn't match
      login(); //restart this function
    }

    std::ofstream file("data\\users\\" + username); //create a file to store the user's details

    file << username << "\n" << password << "\n" << "100"; //Write their username and hashed password as well as 100 free coins to the file

    file.close(); //close the file

    currentUser.username = username; //add that information into the user object so the code can use it
    currentUser.password = password;
    currentUser.balance = 100;

    std::cout << "\n\nUser created succesfully!\n\n"; //there is a bug where this line runs multiple times when the password was not right first try
  } //I have not fixed that bug yet though
  else if(choice == 2) //if the user wants to log in
  {
    std::string username, password, un, pw, bal; //declare variables for the user input and what is in the user's file
    int balance; //declare variable for the balance of the user

    std::cin.sync(); //this is just here so the input is normal
    std::cout << "Enter username: "; //prompt user for their username
    getline(std::cin, username); //get user input
    std::cout << "Enter password: "; //prompt user for their password
    getline(std::cin, password); //get user input
    password = sha256(password); //immediately hash the user's password

    std::ifstream userFile("data\\users\\" + username); //open the file for the user's username
    getline(userFile, un); //get the data from the file on a line by line basis
    getline(userFile, pw);
    getline(userFile, bal);
    userFile.close(); //close the file
    balance = stoi(bal); //turn the string version of bal into the integar balance

    if (un == username && pw == password) //if the username and password match
    {
      currentUser.username = username; //put the data into the currentUser object
      currentUser.password = password;
      currentUser.balance = balance;

      std::cout << "\n\nUser logged in succesfully!\n\n"; //tell user they logged in succesfully, there is also a bug here where this sometimes happens multiple times
    } //when the user got their password wrong
    else
    { //if the user got their password/username wrong
      std::cout << "Invalid login\n"; //tell them it is wrong
      login(); //restart the login process
    } //at some point, I might want to add more detail to this so the user knows exactly what has gone wrong
  }
  else //if the user put in some weird input that was not expected
  {
    std::cout << "Invalid option\n"; //tell the user
    login(); //restart login process
  }
  return currentUser; //return the currentUser object which should have all the information it needs at this point
}
