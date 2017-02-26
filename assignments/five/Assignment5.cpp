#include <iostream>
#include "CommunicationNetwork.h"

using namespace std;

string getUserInputFromMenu() {
  // printing 
  cout << "======Main Menu======" << endl;
  cout << "1. Build Network" << endl;
  cout << "2. Print Network Path" << endl;
  cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
  cout << "4. Add City" << endl;
  cout << "5. Delete City" << endl;
  cout << "6. Clear Network" << endl;
  cout << "7. Quit" << endl;
  string userInput;
  getline(cin, userInput);
  return userInput;
}

int main(int argc, char* argv[]) {
  char* filename = argv[1];
  CommunicationNetwork net = CommunicationNetwork();
  bool exit = false;
  while (!exit) {
    string userInput = getUserInputFromMenu();
    if (userInput == "1") {
      net.buildNetwork();
    } else if (userInput == "2") {
      net.printNetwork();
    } else if (userInput == "3") {
      net.transmitMsg(filename);
    } else if (userInput == "4") {
      string desiredCity;
      string previousCity;
      //cin.clear();    // clear the error flag of cin.
      //cin.ignore(100, '\n');
      cout << "Enter a city name: ";
      getline(cin, desiredCity);
      cout << "\nEnter a previous city name: \n";
      getline(cin, previousCity);
      net.addCity(desiredCity, previousCity);
    } else if (userInput == "5") {
      string cityToRemove;
      cout << "Enter a city name: \n";
      getline(cin, cityToRemove);
      net.deleteCity(cityToRemove);   
    } else if (userInput == "6") {
      net.deleteNetwork();
    } else if (userInput == "7") {
      cout << "Goodbye!" << endl;
      exit = true;
    }
  }
}
