#include <iostream>
#include <sstream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork() {
  head = NULL;
}

CommunicationNetwork::~CommunicationNetwork() {
  deleteNetwork();
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
    head = new City(cityName, NULL, NULL, "");
    return;
  }
  if (previousCity == "First") {
    City *oldHead = head;
    head = new City(cityName, oldHead, NULL, "");
  } else {
    City *temp = head;
    City *newCity = new City(cityName, NULL, NULL, "");
    while (temp -> next != NULL) {
      if (temp -> cityName == previousCity) {
        newCity -> next = temp -> next;
        newCity -> previous = temp;
        newCity -> next -> previous = newCity;
        temp -> next = newCity;
        return;
      }
      temp = temp -> next;
    }
    if (temp -> next == NULL) {
      temp -> next = newCity;
      newCity -> previous = temp;
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
    while (temp -> next != NULL) {
      if (temp -> previous == NULL) {
        temp -> message = currentWord;
      } else {
        temp -> message = temp -> previous -> message;
      }
      cout << temp -> cityName << " received " << currentWord << endl;
      temp -> message = "";
      temp = temp -> next;
    }

    if (temp -> next == NULL) {
      cout << temp -> cityName << " received " << currentWord << endl;
    }

    while (temp -> previous != NULL) {
      temp -> previous -> message = temp -> message;
      temp -> message = "";
      cout << temp -> previous -> cityName << " received " << currentWord << endl;
      temp = temp -> previous;
    }
    /*temp -> message = previous -> message;*/
  }
}

void CommunicationNetwork::printNetwork() {
  if (head == NULL) {
    cout << "===CURRENT PATH===" << endl;
    cout << "NULL" << endl;
    cout << "==================" << endl;
    return;
  }
  cout << "===CURRENT PATH===" << endl;
  City *temp = head;
  cout << "NULL <- ";
  while (temp -> next != NULL) {
    cout << (temp -> cityName) << " <-> ";
    temp = temp -> next;
  }
  cout << temp -> cityName << " -> NULL" << endl;
  cout << "==================" << endl;
}

void CommunicationNetwork::deleteCity(string cityToDelete) {
  City *temp = head;

  while (temp != NULL) {
    if (temp -> cityName == cityToDelete) {
      if (temp -> previous == NULL && temp -> next != NULL) {
        temp -> next -> previous = NULL;
        head = temp -> next;
      } else if (temp -> next == NULL) {
        temp -> previous -> next = NULL;
      } else {
        temp -> next -> previous = temp -> previous;
        temp -> previous -> next = temp -> next;
      }
    }
    temp = temp -> next;
  }
}

void CommunicationNetwork::deleteNetwork() {
  City *temp = head;

  while (temp != NULL) {
    cout << "deleting " << temp -> cityName << endl;
    temp = temp -> next;
  }

  head = NULL;
  tail = NULL;
}
