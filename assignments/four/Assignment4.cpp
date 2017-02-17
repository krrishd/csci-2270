#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

string getUserInputFromMenu() {
  // printing 
  cout << "======Main Menu======" << endl;
  cout << "1. Build Network" << endl;
  cout << "2. Print Network Path" << endl;
  cout << "3. Transmit Message Coast-To-Coast" << endl;
  cout << "4. Add City" << endl;
  cout << "5. Quit" << endl;
  string userInput;
  cin >> userInput;
  return userInput;
}

int main() {
  CommunicationNetwork net = CommunicationNetwork();
  bool exit = false;
  while (!exit) {
    string userInput = getUserInputFromMenu();
    if (userInput == "1") {
      net.buildNetwork();
    } else if (userInput == "2") {
      net.printNetwork();
    } else if (userInput == "3") {
      fstream message;
      string currentLine;
      string messageStr;
      message.open("messageln.txt", ifstream::in);
      while(getline(message, currentLine)) {
        cout << currentLine << endl;
        messageStr += currentLine + " ";
      }
      net.transmitMsg(messageStr);
    } else if (userInput == "4") {
      string desiredCity;
      string previousCity;
      cout << "Enter a city name: ";
      cin >> desiredCity;
      cout << endl;
      cout << "Enter a previous city name: ";
      cin >> previousCity;
      cout << endl;
      net.addCity(desiredCity, previousCity);
    } else if (userInput == "5") {
      exit = true;
    }
  }
}
