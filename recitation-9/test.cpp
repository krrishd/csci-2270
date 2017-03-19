#include <iostream>
#include <stdlib.h>

using namespace std;

/*
I used the count variable to keep track of loops rather than swaps, as loops are
a much better estimator of the actual cost of the algorithm. With the original small
arrays, insertionSort was fastest, with quickSort being a close second. With my large
arrays, quickSort was faster by entire orders of magnitude.
*/

// Global variables
int count;
int largeArray1[1000];
int largeArray2[1000];
int largeArray3[1000];
int largeArray4[1000];

void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        count++;

        while (arr[i] < pivot) {
            count++;
            i++;
         }

        while (arr[j] > pivot) {
            count++;
            j--;
        }

        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void selectSort(int arr[], int n) {
  int index_min_value;
  int temp;
  for (int i=0; i<n-1; i++) {
    count++;
  // outer loop tracks the sorted portion of the list
    index_min_value = i; //set index_min_value to the current index of array
    for (int j=i+1; j < n; j++) // inner loop finds the next smallest value
    {
      count++;
      if (arr[j] < arr[index_min_value])
        index_min_value = j;

    }
    if (index_min_value != i) {
      temp = arr[i];
      arr[i] = arr[index_min_value];
      arr[index_min_value] = temp;
    }
  }
}

void insertionSort (int arr[], int length) {
  int j, temp;
  for (int i = 0; i < length; i++)  {
      count++;
      j = i;
      while (j > 0 && arr[j] < arr[j-1])
      { // move elements over until find the position for next element
        count++;
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
        j--;
      }
  }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubbleSort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n-1; i++) {// Last i elements are already in place
    count++;
    for (j = 0; j < n-i-1; j++){
      count++;
      if (arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}


void printList(int arr[], int length){
  for (int i = 0; i<length; i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

void populateArrays(){
  int number;
  for (int i = 0; i < 1000; i++){
    number = rand() % 101;
    largeArray1[i] = number;
    largeArray2[i] = number;
    largeArray3[i] = number;
    largeArray4[i] = number;
  }
}

int main(){
  //HINT: You should place a counter into each algorithm to see how many time each of them run. Then you can compare them easier.
  //You should use the given print statements for better organization.

  int myArray1[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray2[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray3[] = {12, 13, 5, 4, 7, 18, 9 };
  int myArray4[] = {12, 13, 5, 4, 7, 18, 9 };

  cout << endl;
  cout << " ======== Small array ======= " << endl;
  cout << endl;

  cout << "My original small array is: "<< endl;
  printList(myArray1,7);

  //selectSort
  count = 0;
  selectSort(myArray1,7);
  cout<<"When ordered with selectSort, after "<<count<<" operations the result is: "<<endl;
  printList(myArray1,7);

  //insertionSort
  count = 0;
  insertionSort(myArray2,7);
  cout<<"When ordered with insertionSort, after "<<count<<" operations the result is: "<<endl;
  printList(myArray2,7);

  //bubbleSort
  count = 0;
  bubbleSort(myArray3,7);
  cout<<"When ordered with bubbleSort, after "<<count<<" operations the result is: "<<endl;
  printList(myArray3,7);

  //quickSort
  count = 0;
  quickSort(myArray4,0,6);
  cout<<"When ordered with quickSort, after "<<count<<" operations the result is: "<<endl;
  printList(myArray4,7);

  cout << endl;
  cout << " ======== Large array ======= " << endl;
  cout << endl;

  //Begin with large arrays; test with each case and use the same print statements.
  populateArrays();

  cout << "My original large array is: " << endl;
  cout << endl;
  printList(largeArray1, 1000);
  cout << endl;

  //selectSort
  count = 0;
  selectSort(largeArray1, 1000);
  cout<<"When ordered with selectSort, after "<<count<<" operations the result is: "<<endl;
  //printList(largeArray1, 1000);

  //insertionSort
  count = 0;
  insertionSort(largeArray2, 1000);
  cout<<"When ordered with insertionSort, after "<<count<<" operations the result is: "<<endl;
  //printList(largeArray2, 1000);

  //bubbleSort
  count = 0;
  bubbleSort(largeArray3, 1000);
  cout<<"When ordered with bubbleSort, after "<<count<<" operations the result is: "<<endl;
  //printList(largeArray3, 1000);

  //quickSort
  count = 0;
  quickSort(largeArray4, 0, 999);
  cout<<"When ordered with quickSort, after "<<count<<" operations the result is: "<<endl;
  printList(largeArray4, 1000);


  return 0;
}