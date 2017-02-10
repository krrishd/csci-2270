#include <iostream>
#include "WordAnalysis.h"
#include <fstream>
#include <sstream>

using namespace std;

// CONVENIENCE METHODS

// finds index of a word within an array of Word structs
int findWordIndex(word *arrayOfWords, int lengthOfArray, string wordBeingFound) {
  int index = -1;
  for (int i = 0; i < lengthOfArray; i++) {
    if (arrayOfWords[i].w == wordBeingFound) {
      index = i;
      break;
    }
  }
  return index;
}

// array doubling logic
void doubleWordArraySize(word **arrayOfWords, int *currentSize, int *timesDoubled) {
  int desiredSize = *currentSize * 2;
  word *doubledArray = new word[desiredSize];
  for (int i = 0; i < *currentSize; i++) {
    doubledArray[i] = (*arrayOfWords)[i];
  }
  delete [] (*arrayOfWords);
  *currentSize = desiredSize;
  *arrayOfWords = doubledArray;
  *timesDoubled = *timesDoubled + 1;
}

// prints words based on spec format
void printWords(word *arrayOfWords, int numToPrint) {
  for(int i = 0; i < numToPrint; i++) {
    cout << arrayOfWords[i].count << " - " << arrayOfWords[i].w << endl;
  }
}

// CONSTRUCTOR / DESTRUCTOR

WordAnalysis::WordAnalysis(int initialSize) {
  timesDoubled = 0;
  words = new word[initialSize];
  wordCount = initialSize;
  index = 0;
}

WordAnalysis::~WordAnalysis() {

}

// PRIVATE METHODS

void WordAnalysis::doubleArrayAndAdd(std::string currentWord) {
    int wordIndex = findWordIndex(words, wordCount, currentWord);
    if (wordCount == index) {
      doubleWordArraySize(&words, &wordCount, &timesDoubled);
    }
    if (wordIndex == -1) {
      word newWord;
      newWord.w = currentWord;
      newWord.count = 1;
      words[index] = newWord;
      index++;
    } else {
      words[wordIndex].count = words[wordIndex].count + 1;
    }
}

bool WordAnalysis::checkIfCommonWord(std::string word) {
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

void WordAnalysis::sortData() {
  int j;
  int currentIndex = index;
  word tempWord;
  for (int i = 0; i < currentIndex; i++) {
    j = i;
    while (j > 0 && words[j].count > words[j-1].count) {
      tempWord = words[j];
      words[j] = words[j-1];
      words[j-1] = tempWord;
      j--;
    }
  }
}

// PUBLIC METHODS

bool WordAnalysis::readDataFile(char*filename) {
  int totalCount = 0;
  ifstream whirds;
  whirds.open(filename, ifstream::in);
  string currentLine;
  while(getline(whirds, currentLine)) {
    stringstream ssline(currentLine);
    string currentWord;
    while(getline(ssline, currentWord, ' ')) {
      if (checkIfCommonWord(currentWord)) {
        doubleArrayAndAdd(currentWord);
        totalCount++;
      }
    }
  }
  wordCount = totalCount;
  sortData();
  return true;
}

int WordAnalysis::getWordCount() {
  return wordCount;
}

int WordAnalysis::getUniqueWordCount() {
  return index;
}

int WordAnalysis::getArrayDoubling() {
  return timesDoubled;
}

void WordAnalysis::printCommonWords(int numToPrint) {
  printWords(words, numToPrint);
}