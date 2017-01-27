// Name: Krishna Dholakiya
// Assignment #1
// Instructor: Rhonda Hoenigman

#include <iostream>;
#include <fstream>;
#include <sstream>;

using namespace std;

struct Product {
  string item;
  string status;
  int price;
};

void printProduct(Product prod, bool statusMatters) {
  if(statusMatters) {
    cout << prod.item << ", " << prod.status << ", " << prod.price << endl;
  } else {
    cout << prod.item << " " << prod.price << endl;
  }
}

// finds index of product that complements another
int matchIndex(
    Product list[], 
    Product referenceProduct, 
    string statusSought,
    int listLength,
    int *searchCounter
  ) {
  int index = -1;
  for(int i = 0; i < listLength; i++) {
    Product potentialMatch = list[i];
    bool priceMatches = false;
    if (statusSought == "wanted") {
      priceMatches = (potentialMatch.price >= referenceProduct.price);
    } else {
      priceMatches = (potentialMatch.price <= referenceProduct.price);
    }
    if (
      (potentialMatch.item == referenceProduct.item) &&
      (potentialMatch.status == statusSought) &&
      priceMatches
    ) {
      index = i;
      break;
    }
    *searchCounter = *searchCounter + 1;
  }
  return index;
}

// loads message board file, populates array with items, conducts matching of said items
int populateMessageBoard(Product list[], string filename, int *fileCounter, int *searchCounter, int *shiftCounter) {
  ifstream messageBoard;
  messageBoard.open(filename, ifstream::in);
  string currentLine;
  int listIndex = 0;
  while(getline(messageBoard, currentLine)) {
    stringstream ssline(currentLine);
    string column;
    string statusSought;
    int positionInRow = 0;
    Product currentProduct;
    while(getline(ssline, column, ',')) {
      if (positionInRow == 0) {
        currentProduct.item = column;
      } else if (positionInRow == 1) {
        currentProduct.status = column.erase(0,1);
        if (column == "wanted") {
          statusSought = "for sale";
        } else {
          statusSought = "wanted";
        }
      } else if (positionInRow == 2) {
        currentProduct.price = stoi(column.erase(0,1));
      }
      positionInRow++;
    }
    int potentialMatchIndex = matchIndex(list, currentProduct,statusSought, (listIndex + 1), searchCounter);
    if (potentialMatchIndex == -1) {
      list[listIndex] = currentProduct;
      listIndex++;
    } else {
      if (currentProduct.status == "wanted") {
        printProduct(list[potentialMatchIndex], false);
      } else {
        printProduct(currentProduct, false);
      }
      for (int i = potentialMatchIndex; i < listIndex - 1; i++) {
        list[i] = list[i + 1];
        *shiftCounter = *shiftCounter + 1;
      }
      listIndex = listIndex - 1;
    }
    *fileCounter = *fileCounter + 1;
  }
  return listIndex;
}

// prints the message board as a list
void printMessageBoard(Product list[], int listLength) {
  for (int i = 0; i < listLength; i++) {
    printProduct(list[i], true);
  }
}

int main() {
  Product list[100];
  int localFileCounter = 0;
  int localSearchCounter = 0;
  int localShiftCounter = 0;
  int *fileCounter = &localFileCounter;
  int *searchCounter = &localSearchCounter;
  int *shiftCounter = &localShiftCounter;

  string filename;
  cin >> filename;

  int listSize = populateMessageBoard(list, filename, fileCounter, searchCounter, shiftCounter);
  cout << "#" << endl;
  printMessageBoard(list, listSize);
  cout << "#" << endl;
  cout<<"file read:"<<localFileCounter<<endl;
  cout<<"search array:"<<localSearchCounter<<endl;
  cout<<"shift array:"<<localShiftCounter<<endl;
}
