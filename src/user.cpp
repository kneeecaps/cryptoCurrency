#include <fstream>

#include "user.hpp"

void user::update() //one function, to update the user's file with whatever values are stored in the object
{
  std::ofstream userFile("data\\users\\" + username); //open the file

  userFile << username << "\n" << password << "\n" << std::to_string(balance); //write whatevers in the object to the file

  userFile.close(); //close the file to save memory
}
