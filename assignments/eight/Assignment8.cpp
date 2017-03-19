/*
* Name: Krishna Dholakiya
* TA: Mridula Natarajan
* Instructor: Rhonda Hoenigman
* Assignment #8
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "MovieTree.h"


using namespace std;

int menu() {
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Rent a movie" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Delete a movie" << endl;
  cout << "5. Count the movies" << endl;
  cout << "6. Quit" << endl;
  
  string userInput;
  getline(cin, userInput);

  return stoi(userInput);
}

int main(int argc, char * argv[]) {
  char* filename = argv[1];
  MovieTree tree;
  string data;
  string dataProcessed;

  int counter = 0, rankNumber = 0, release = 0, availableCopies = 0;
  string title;

  ifstream inFile(filename);
  while (getline(inFile, data)) {
    stringstream ss(data);
    while (getline(ss, dataProcessed, ',')) {
      if (counter == 0) {
        rankNumber = stoi(dataProcessed);
        counter++;
      } else if (counter == 1) {
        title = dataProcessed;
        counter++;
      } else if (counter == 2) {
        release = stoi(dataProcessed);
        counter++;
      } else if (counter == 3) {
        availableCopies = stoi(dataProcessed);
        counter = 0;
      }
    }
    tree.addMovieNode(rankNumber, title, release, availableCopies);
  }

  bool quit = false;

  while (!quit) {
    int userInput = menu();

    string toFind, toRent, toDelete;
    switch(userInput) {
      case 1:
        cout << "Enter title:" << endl;
        getline(cin, toFind);
        tree.findMovie(toFind);
        break;
      case 2:
        cout << "Enter title:" << endl;
        getline(cin, toRent);
        tree.rentMovie(toRent);
        break;
      case 3:
        tree.printMovieInventory();
        break;
      case 4:
        cout << "Enter title:" << endl;
        getline(cin, toDelete);
        tree.deleteMovieNode(toDelete);
        break;
      case 5:
        cout << "Tree contains: " << tree.countMovieNodes() << " movies." << endl;
        break;
      case 6:
        cout << "Goodbye!" << endl;
        quit = true;
      default:
        break;
    }
  }
  return 0;
}
