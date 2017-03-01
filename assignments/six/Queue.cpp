#include <iostream>
#include <sstream>
#include <string>
#include "Queue.h"

using namespace std;

Queue::Queue(int qs) {
  queueSize = qs;
  queueCurrentSize = 0;
  arrayQueue = new string[queueSize];
  queueHead = 0;
  queueTail = 0;
}

Queue::~Queue() {

}

void Queue::enqueue(string toEnqueue) {
  if (queueIsFull()) {
    cout << "Queue is full." << endl;
    return;
  }

  arrayQueue[queueTail] = toEnqueue;
  queueCurrentSize++;

  if (queueTail == queueSize - 1) {
    queueTail = 0;
  } else {
    queueTail++;
  }

  cout << "E: " << toEnqueue << endl;
  cout << "H: " << queueHead << endl;
  cout << "T: " << queueTail << endl;
}

void Queue::enqueueSentence(string toEnqueue) {
  stringstream s(toEnqueue);
  string currentWord;
  while (getline(s, currentWord, ' ')) {
    enqueue(currentWord);
  }
}

string Queue::dequeue() {
  if (queueIsEmpty()) {
    cout << "Queue is empty." << endl;
    return "";
  }
  
  string toDelete = arrayQueue[queueHead];
  arrayQueue[queueHead] = "";
  queueCurrentSize--;

  if (queueHead == queueSize - 1) {
    queueHead = 0;
  } else {
    queueHead++;
  }

  cout << "H: " << queueHead << endl;
  cout << "T: " << queueTail << endl;
  cout << "word: " << toDelete << endl;
}

void Queue::printQueue() {
  if (queueIsEmpty()) {
    cout << "Empty" << endl;
    return;
  }

  for (int i = queueHead; i < queueSize; i++) {
    if (arrayQueue[i] != "") {
      cout << i << ": " << arrayQueue[i] << endl;
    }
  } 

  for (int j = 0; j < queueHead; j++) {
    if (arrayQueue[j] != "") {
      cout << j << ": " << arrayQueue[j] << endl;
    }
  }
}

bool Queue::queueIsEmpty() {
  return (queueCurrentSize == 0);
}

bool Queue::queueIsFull() {
  return (queueCurrentSize == queueSize);
}
