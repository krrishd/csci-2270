#include <iostream>;

using namespace std;

void InsertionSort(int array[], int len) {
  for(int i = 1; i < len; i++) {
    int index =  array[i];
    int j = i;
    while (j > 0 && array[j - 1] > index) {
      array[j] = array[j - 1];
      j = j - 1;
    }
    array[j] = index;
    for(int z = 0; z < len; z++) {
      cout << array[z] << " ";   
    }
    cout << "\n";
  }
}

int main() {
  int arr[8] = {5,1,3,6,4,8,7,2};
  InsertionSort(arr, 8);
}
