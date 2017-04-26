#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int getMenuInput() {
  string userInput;

  cout << "======Main Menu======" << endl;
  cout << "1. Print vertices" << endl;
  cout << "2. Find districts" << endl;
  cout << "3. Find shortest path" << endl;
  cout << "4. Quit" << endl;
  
  getline(cin, userInput);
  return stoi(userInput);
}

int main(int argc, char * argv[]) {
    char* filename = argv[1];
    Graph<string> g;
    g.populateWithFileContents(filename);

    bool active = true;
    while (active) {
      string startingCity;
      string endingCity;

      switch(getMenuInput()) {
        case 1:
          g.displayEdges();
          break;
        case 2:
          g.assignDistricts();
          break;
        case 3:
          cout << "Enter a starting city:" << endl;
          getline(cin, startingCity);
          cout << "Enter an ending city:" << endl;
          getline(cin, endingCity);
          g.shortestPath(startingCity, endingCity);
          break;
        case 4:
          active = false;
          cout << "Goodbye!" << endl;
          break;
        default:
          break;
      }
    }
}