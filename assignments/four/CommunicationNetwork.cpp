#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork() {
  head = NULL;
}

CommunicationNetwork::~CommunicationNetwork() {

}

void CommunicationNetwork::buildNetwork() {
  addCity("Los Angeles", "");
  addCity("Phoenix", "Los Angeles");
  addCity("Denver", "Phoenix");
  addCity("Dallas", "Denver");
  addCity("St. Louis", "Dallas");
  addCity("Chicago", "St. Louis");
  addCity("Atlanta", "Chicago");
  addCity("Washington, D.C.", "Atlanta");
  addCity("New York", "Washington, D.C.");
  addCity("Boston", "New York");
  printNetwork();
}

void CommunicationNetwork::addCity(string cityName, string previousCity) {
  if (head == NULL) {
    head = new City(cityName, NULL, "");
    return;
  }
  if (previousCity == "First") {
    City *oldHead = head;
    head = new City(cityName, oldHead, "");
  } else {
    City *temp = head;
    City *newCity = new City(cityName, NULL, "");
    while (temp -> next != NULL) {
      if (temp -> cityName == previousCity) {
        newCity -> next = temp -> next;
        temp -> next = newCity;
        return;
      }
      temp = temp -> next;
    }
    if (temp -> next == NULL) {
      temp -> next = newCity;
    }
  }
}

void CommunicationNetwork::transmitMsg(char * filename) {
  fstream message;
  string currentLine;
  string messageStr;
  message.open(filename, fstream::in);
  while(getline(message, currentLine)) {
    messageStr += currentLine + " ";
  }
  if (head == NULL) {
    cout << "Empty list" << endl;
    return;
  }
  stringstream ssline(messageStr);
  string currentWord;
  City *temp;
  City *previous;
  while(getline(ssline, currentWord, ' ')) {
    temp = head;
    previous = NULL;
    while (temp != NULL) {
      if (previous == NULL) {
        temp -> message = currentWord;
      } else {
        temp -> message = previous -> message;
      }
      cout << temp -> cityName << " received " << currentWord << endl;
      previous = temp;
      temp -> message = "";
      temp = temp -> next;
    }
    /*temp -> message = previous -> message;*/
  }
}

void CommunicationNetwork::printNetwork() {
  if (head == NULL) {
    cout << "Empty list" << endl;
    return;
  }
  cout << "===CURRENT PATH===" << endl;
  City *temp = head;
  while (temp -> next != NULL) {
    cout << (temp -> cityName) << " -> ";
    temp = temp -> next;
  }
  cout << temp -> cityName << " -> NULL" << endl;
  cout << "==================" << endl;
}
