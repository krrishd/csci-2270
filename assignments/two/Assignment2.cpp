/*
Name: Krishna Dholakiya
Assignment #2
Instructor: Rhonda Hoenigman
 */

#include <iostream>;
#include <fstream>;
#include <sstream>;

using namespace std;

struct Word {
  string content;
  int count;
};

// finds index of a word within an array of Word structs
int findWordIndex(word *arrayOfWords, int lengthOfArray, string wordBeingFound) {
  int index = -1;
  for (int i = 0; i < lengthOfArray; i++) {
    if (arrayOfWords[i].content == wordBeingFound) {
      index = i;
      break;
    }
  }
  return index;
}

// array doubling logic
void doubleWordArraySize(Word **arrayOfWords, int *currentSize, int *timesDoubled) {
  int desiredSize = *currentSize * 2;
  Word *doubledArray = new Word[desiredSize];
  for (int i = 0; i < *currentSize; i++) {
    doubledArray[i] = (*arrayOfWords)[i];
  }
  delete [] (*arrayOfWords);
  *currentSize = desiredSize;
  *arrayOfWords = doubledArray;
  *timesDoubled = *timesDoubled + 1;
}

// determines whether or not word is to be counted
bool isValidWord(string word) {
  bool status = true;

  string badWordList[51] = {"the", "be", "to", "of", "and", "a", "in", "that",
    "have", "i", "it", "for", "not", "on", "with", "he",
    "as", "you", "do", "at", "this", "but", "his", "by",
    "from", "they", "we", "say", "her", "she", "or", "an",
    "will", "my", "one", "all", "would", "there", "their",
    "what", "so", "up", "out", "if", "about", "who",
    "get", "which", "go", "me", ""};
  
  for (int i = 0; i < 51; i++) {
    if (badWordList[i] == word) {
      status = false;
      break;
    }
  }

  return status;
}

// opens file, filters thru lines/spaces, determines whether
// word is already present in array; if word is present, increments its count,
// otherwise adds word to array of structs
void populateWordArray(Word **arrayOfWords, int *lengthOfArray, int *lengthUsed, string filename, int *timesDoubled, int *total) {
  ifstream words;
  words.open(filename, ifstream::in);
  string currentLine;
  while(getline(words, currentLine)) {
    stringstream ssline(currentLine);
    string currentWord;
    while(getline(ssline, currentWord, ' ')) {
      if (isValidWord(currentWord)) {
        int wordIndex = findWordIndex(*arrayOfWords, *lengthOfArray, currentWord);
        if (*lengthUsed == *lengthOfArray) {
          doubleWordArraySize(arrayOfWords, lengthOfArray, timesDoubled);
        }
        if (wordIndex == -1) {
          Word newWord;
          newWord.content = currentWord;
          newWord.count = 1;
          (*arrayOfWords)[*lengthUsed] = newWord;
          *lengthUsed = *lengthUsed + 1;
        } else {
          //Word tempWord = arrayOfWords[wordIndex];
          (*arrayOfWords)[wordIndex].count++;
        }
        *total = *total + 1;
      }
    }
  }
}

// uses insertion sort to sort words in array by count
void sortWordArray(Word *arrayOfWords, int lengthUsed) {
  int j;
  int currentIndex = lengthUsed;
  Word tempWord;
  for (int i = 0; i < currentIndex; i++) {
    j = i;
    while (j > 0 && arrayOfWords[j].count > arrayOfWords[j-1].count) {
      tempWord = arrayOfWords[j];
      arrayOfWords[j] = arrayOfWords[j-1];
      arrayOfWords[j-1] = tempWord;
      j--;
    }
  }
}

// prints words based on spec format
void printWords(Word *arrayOfWords, int numToPrint) {
  for(int i = 0; i < numToPrint; i++) {
    cout << arrayOfWords[i].count << " - " << arrayOfWords[i].content << endl;
  }
}

int main(int argc, char *argv[]) {
  string filename = argv[1];
  int topWords = stoi(argv[2]);
  int currentArraySize = 100;
  int lengthUsed = 0;
  int total = 0;
  int numberOfTimesDoubled = 0;
  int *lengthUsedPointer = &lengthUsed;
  int *arraySizePointer = &currentArraySize;
  int *timesDoubledPointer = &numberOfTimesDoubled;
  int *totalPointer = &total;
  Word *arrayOfWords = new Word[currentArraySize];
  populateWordArray(&arrayOfWords,arraySizePointer, lengthUsedPointer, filename, timesDoubledPointer, totalPointer);
  sortWordArray(arrayOfWords, lengthUsed);
  printWords(arrayOfWords, topWords);
  cout << "#" << endl << "Array doubled: " << numberOfTimesDoubled << endl;
  cout << "#" << endl << "Unique non-common words: " << lengthUsed << endl;
  cout << "#" << endl << "Total non-common words: " << total << endl;

  /*delete lengthUsedPointer, arraySizePointer, timesDoubledPointer, totalPointer;
  delete [] arrayOfWords;*/
}