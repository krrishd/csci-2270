#include <iostream>
#include <string>
#include <queue>
//TODO: add appropriate includes

using namespace std;

// ----------------------------------------------------------------------
class customVector{
  public:
    //TODO: add appropriate header information
    vector<int> intVec;
    void printVector();
    void reverseVector();
    void removeAll();
    void removeElement(int);
};
// ----------------------------------------------------------------------
void customVector::printVector(){
  cout << "Elements of Integer Vector: " << endl;
  // TODO: check if the vector is empty otherwise print all elements in the vector
  if (intVec.size() == 0) {
    return;
  }
  
  for (int i : intVec) {
    cout << i << endl;
  }
}

void customVector::reverseVector(){
  //TODO: reverse the elements in the vector, using the STL algorithm
  reverse(intVec.begin(), intVec.end());
}

void customVector::removeAll(){
  cout << "Removing all elements from the vector: " << endl;
  //TODO: remove all elements from the vector
  intVec.clear();
}

void customVector::removeElement(int n){
  //TODO: remove a specific element from the vector
  int indexToDelete = -1;
  for (int i : intVec) {
    if (i == n) {
      indexToDelete = i;
    }
  }

  intVec.erase(intVec.begin() + indexToDelete);
}

// ----------------------------------------------------------------------
int main(){
  customVector vec1;
  auto numbers = {1,2,3,4,5,6,7,8};
  for (auto num : numbers){
    vec1.intVec.push_back(num);
  }

  vec1.printVector();

  vec1.reverseVector();
  vec1.printVector();

  vec1.removeElement(4);
  vec1.printVector();

  vec1.removeAll();
  vec1.printVector();

  return 0;
}
