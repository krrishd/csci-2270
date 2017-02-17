#include <iostream>
#include <sstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork() {

}

CommunicationNetwork::~CommunicationNetwork() {

}

void CommunicationNetwork::buildNetwork() {
  addCity("Los Angeles", "First");
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
    City *newCity = new City(cityName, NULL, "");
    head = newCity;
  } else if (previousCity == "First") {
    City *oldHead = head; 
    City *newCity = new City(cityName, oldHead, "");
    head = newCity;
  } else {
    City *temp = head;
    City *newCity = new City(cityName, NULL, "");
    while (temp -> next != NULL) {
      if (temp -> cityName == previousCity) {
        newCity -> next = temp -> next;
        temp -> next = newCity;
        break;
      }
      temp = temp -> next;
    }
    
  }
}

void CommunicationNetwork::transmitMsg(string msg) {
  cout << "transmitting " << msg << endl;
  stringstream ssline(msg);
  string currentWord;
  while(getline(ssline, currentWord, ' ')) {
    cout << currentWord << endl;
    City *temp = head;
    City *previous;
    while (temp -> next != NULL) {
      if (previous == NULL) {
        temp -> message = currentWord;
      } else {
        temp -> message = previous -> message;
      }
      cout << temp -> cityName << " received " << temp -> message << endl;
      previous = temp;
      temp -> message = "";
      temp = temp -> next;
    }
    temp -> message = previous -> message;
  }
}

void CommunicationNetwork::printNetwork() {
  cout << "===CURRENT PATH===" << endl;
  City *temp = head;
  while (temp -> next != NULL) {
    cout << (temp -> cityName) << " -> ";
    temp = temp -> next;
  }
  cout << temp -> cityName << " -> NULL" << endl;
  cout << "==================" << endl;
}
