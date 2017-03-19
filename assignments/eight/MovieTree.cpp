#include <iostream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  DeleteAll(root);
}

void MovieTree::printMovieInventory(MovieNode * node) {
  if (node -> leftChild != NULL) {
    printMovieInventory(node -> leftChild);
  }

  cout << "Movie: " << node -> title << " " << node -> quantity << endl;

  if (node -> rightChild != NULL) {
    printMovieInventory(node -> rightChild);
  }
}

void MovieTree::printMovieInventory() {
  printMovieInventory(root);
}

int MovieTree::countMovieNodes(MovieNode * node) {
  if (!node) {
    return 0;
  }
  return countMovieNodes(node -> leftChild) + countMovieNodes(node -> rightChild) + 1;
}

int MovieTree::countMovieNodes() {
  int *c = 0;
  return countMovieNodes(root);
}

void MovieTree::deleteMovieNode(string title) {
  MovieNode * temp =root;

  while (temp != NULL){
    if (temp->title == title){
      if (temp->leftChild == NULL and temp->rightChild == NULL){
        if (temp->parent->leftChild == temp){
          temp->parent->leftChild = NULL;
        } else{
          temp->parent->rightChild = NULL;
        }
        delete temp;
        break;
      }
      if (temp->leftChild != NULL and temp->rightChild != NULL){
        MovieNode * minNode = temp->rightChild;
        while (minNode->leftChild != NULL){
          minNode = minNode->leftChild;
        }
        if (minNode->parent == temp){
          if (temp->parent->leftChild == temp){
            temp->parent->leftChild = minNode;
            minNode->parent = temp->parent;
            temp->leftChild->parent = minNode;
            minNode->leftChild = temp->leftChild;
          } else{
            temp->parent->rightChild = minNode;
            minNode->parent = temp->parent;
            temp->leftChild->parent = minNode;
            minNode->leftChild = temp->leftChild;
          }
        } else{
          if (temp->parent->leftChild == temp){
            if (minNode->rightChild != NULL){
              minNode->parent->leftChild = minNode->rightChild;
              minNode->rightChild->parent = minNode->parent;
            }
            minNode->parent = temp->parent;
            temp->parent->leftChild = minNode;
            minNode->leftChild = temp->leftChild;
            minNode->rightChild = temp->rightChild;
            temp->rightChild->parent = minNode;
            temp->leftChild->parent = minNode;
          } else{
            if (minNode->rightChild != NULL){
              minNode->parent->leftChild = minNode->rightChild;
              minNode->rightChild->parent = minNode->parent;
            }
            minNode->parent = temp->parent;
            temp->parent->rightChild = minNode;
            minNode->leftChild = temp->leftChild;
            minNode->rightChild = temp->rightChild;
            temp->rightChild->parent = minNode;
            temp->leftChild->parent = minNode;
          }
        }
        delete temp;
        break;
      }
      else{
        if (temp->leftChild){
          MovieNode * x = temp->leftChild;
          if (temp->parent->leftChild == temp){
            temp->parent->leftChild = temp->leftChild;
          }
          else {
            temp->parent->rightChild = temp->leftChild;
          }
          temp->leftChild->parent = temp->parent;
        } else{
          MovieNode * x =temp->rightChild;
          if (temp->parent->rightChild == temp){
              temp->parent->rightChild = x;
          }
          else {
              temp->parent->leftChild = x;
          }
          x->parent = temp->parent;
          delete temp;
          break;
        }
      }
    }
    
    else if (temp->title.compare(title) > 0){
      temp = temp->leftChild;
    }
    else{
      temp = temp->rightChild;
    }
  }
  
  if (temp == NULL){
    cout << "Movie not found." << endl;
  }
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
  MovieNode * toAdd = new MovieNode(ranking, title, releaseYear, quantity);
  MovieNode * temp = root;
  MovieNode * parent = NULL;

  if (root == NULL) {
    root = toAdd;
  } else {
    while (temp != NULL) {
      parent = temp;
      if ((parent -> title).compare(toAdd -> title) > 0) {
        temp = temp -> leftChild;
      } else {
        temp = temp -> rightChild;
      }
    }

    if ((parent -> title).compare(toAdd -> title) > 0) {
      parent -> leftChild = toAdd;
      toAdd -> parent = parent;
    } else {
      parent -> rightChild = toAdd;
      toAdd -> parent = parent;
    }
  }
}

void MovieTree::findMovie(string title) {
  bool found = false;
  MovieNode * temp = root;
  while (temp != NULL) {
    if ((temp -> title).compare(title) > 0) {
      temp = temp -> leftChild;
    } else if ((temp -> title).compare(title) < 0) {
      temp = temp -> rightChild;
    } else {
      cout << "Movie Info:" << endl;
      cout << "===========" << endl;
      cout << "Ranking:" << temp->ranking << endl; //info
      cout << "Title:" << temp->title << endl;
      cout << "Year:" << temp->year << endl;
      cout << "Quantity:" << temp->quantity << endl;
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "Movie not found." << endl;
  }
}

void MovieTree::rentMovie(string title) {
  bool found = false;
  MovieNode * temp = root;
  while (temp != NULL) {
    if (temp -> title.compare(title) > 0) {
      temp = temp -> leftChild;
    } else if (temp -> title.compare(title) < 0) {
      temp = temp -> rightChild;
    } else {
      found = true;
      if (temp -> quantity > 0) {
        temp -> quantity = temp -> quantity - 1;
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << temp->ranking << endl; //info
        cout << "Title:" << temp->title << endl;
        cout << "Year:" << temp->year << endl;
        cout << "Quantity:" << temp->quantity << endl;
        if (temp -> quantity == 0) {
          deleteMovieNode(temp -> title);
        }
      } else {
        cout << "Movie out of stock." << endl;
      }

      break;
    }
  }

  if (!found) {
    cout << "Movie not found." << endl;
  }
}

void MovieTree::DeleteAll(MovieNode * node) {
  if (node -> leftChild != NULL) {
    DeleteAll(node -> leftChild);
  }

  if (node -> rightChild != NULL) {
     DeleteAll(node -> rightChild);
  }

  cout << "Deleting: " << node -> title << endl;
  delete node;
}

MovieNode* search(string title) {

}

MovieNode* searchRecursive(MovieNode * node, string value) {

}

MovieNode* treeMinimum(MovieNode *node) {

}


