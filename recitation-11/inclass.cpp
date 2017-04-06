#include <iostream>
#include <queue>

using namespace std;

int main() {
  queue<int> myQueue;
  cout << "Size: " <<  myQueue.size() << endl;
  myQueue.push(3);
  myQueue.push(6);
  myQueue.push(5);
  cout << "Size: " << myQueue.size() << endl;
  while (!myQueue.empty()) {
    myQueue.pop();
  }
  cout << "Size: " << myQueue.size() << endl;
}

