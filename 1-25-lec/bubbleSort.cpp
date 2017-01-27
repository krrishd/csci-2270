#include <iostream>

using namespace std;

void bubbleSort(int A[], int length) {
  for(int i = 0; i < length - 1; i++) {
    for(int j = 0; j < length - i - 1; j++) {
      if (A[j] > A[j + 1]) {
        int swap = A[j];
        A[j] = A[j + 1];
        A[j + 1] = swap;
      }
    }
  }
}

int main() {
  int A[4] = {45, 44, 32, 23};
  bubbleSort(A, 4);
  for(int i = 0; i < 4; i++) {
    cout << A[i] << endl;
  } // expected: 23, 32, 44, 45
}
