/*
 * Assignment #6
 * Name: Krishna Dholakiya
 * TA: Mridula Natarajan
 * Instructor: Rhonda Hoenigman
 */

#include <iostream>
#include "Queue.h"

using namespace std;

string menu() {
  cout << "======Main Menu=====" << endl;
  cout << "1. Enqueue word" << endl;
  cout << "2. Dequeue word" << endl;
  cout << "3. Print queue" << endl;
  cout << "4. Enqueue sentence" << endl;
  cout << "5. Quit" << endl;
  
  string userInput;
  getline(cin, userInput);
  return userInput;
}

int main() {

  Queue q(10);

  bool quit = false;

  string toEnqueue;
  string sentence;

  while (!quit) {
    int userInput = stoi(menu());
    switch (userInput) {
      case 1: cout << "word: ";
                //string toEnqueue;
                getline(cin, toEnqueue);
                q.enqueue(toEnqueue);
                break;
      case 2: q.dequeue();
              break;
      case 3: q.printQueue();
              break;
      case 4: cout << "sentence: ";
                //string sentence;
                getline(cin, sentence);
                q.enqueueSentence(sentence);
                break;
      case 5: quit = true;
              break;
    }
  }

  cout << "Goodbye!" << endl;
}
