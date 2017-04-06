#include <iostream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree(){
  nil = new MovieNode(0, "", 0, 0);
  nil -> isRed = false;
  nil -> leftChild = nil->rightChild = nil;
  root = nil;
}

MovieTree::~MovieTree(){
  DeleteAll(root);
}

void MovieTree::printMovieInventory(MovieNode * node){
  if (node -> leftChild != nil){
    printMovieInventory(node -> leftChild);
  }

  cout << "Movie: " << node -> title << " " << node -> quantity << endl;

  if (node -> rightChild != nil){
    printMovieInventory(node -> rightChild);
  }
}

void MovieTree::printMovieInventory(){
  printMovieInventory(root);
}

int MovieTree::countMovieNodes(MovieNode * node){
  if (node == nil){
    return 0;
  }
  return countMovieNodes(node -> leftChild)+ countMovieNodes(node -> rightChild)+ 1;
}

int MovieTree::countMovieNodes(){
  int *c = 0;
  return countMovieNodes(root);
}

int MovieTree::countLongestPath(){
    int longestPath = countLongestPath(root);
    return longestPath;
}

int MovieTree::countLongestPath(MovieNode * node){
  if (node == nil){
    return 0;
  }
  int longestRightPath = countLongestPath(node -> rightChild);
  int longestLeftPath = countLongestPath(node -> leftChild);
  if (longestLeftPath > longestRightPath){
    return longestLeftPath + 1;
  } else {
    return longestRightPath + 1;
  }
}


void MovieTree::deleteMovieNode(string title){
  MovieNode * temp =root;

  while (temp != nil){
    if (temp -> title == title){
      if (temp -> leftChild == nil and temp -> rightChild == nil){
        if (temp -> parent -> leftChild == temp){
          temp -> parent -> leftChild = nil;
        } else{
          temp -> parent -> rightChild = nil;
        }
        delete temp;
        break;
      }
      if (temp -> leftChild != nil and temp -> rightChild != nil){
        MovieNode * minNode = temp -> rightChild;
        while (minNode -> leftChild != nil){
          minNode = minNode -> leftChild;
        }
        if (minNode -> parent == temp){
          if (temp -> parent -> leftChild == temp){
            temp -> parent -> leftChild = minNode;
            minNode -> parent = temp -> parent;
            temp -> leftChild -> parent = minNode;
            minNode -> leftChild = temp -> leftChild;
          } else{
            temp -> parent -> rightChild = minNode;
            minNode -> parent = temp -> parent;
            temp -> leftChild -> parent = minNode;
            minNode -> leftChild = temp -> leftChild;
          }
        } else{
          if (temp -> parent -> leftChild == temp){
            if (minNode -> rightChild != nil){
              minNode -> parent -> leftChild = minNode -> rightChild;
              minNode -> rightChild-> parent = minNode -> parent;
            }
            minNode -> parent = temp -> parent;
            temp -> parent -> leftChild = minNode;
            minNode -> leftChild = temp -> leftChild;
            minNode -> rightChild = temp -> rightChild;
            temp -> rightChild -> parent = minNode;
            temp -> leftChild -> parent = minNode;
          } else{
            if (minNode -> rightChild != nil){
              minNode -> parent -> leftChild = minNode -> rightChild;
              minNode -> rightChild -> parent = minNode -> parent;
            }
            minNode -> parent = temp -> parent;
            temp -> parent -> rightChild = minNode;
            minNode -> leftChild = temp -> leftChild;
            minNode -> rightChild = temp -> rightChild;
            temp -> rightChild -> parent = minNode;
            temp -> leftChild -> parent = minNode;
          }
        }
        delete temp;
        break;
      }
      else{
        if (temp -> leftChild){
          MovieNode * x = temp -> leftChild;
          if (temp -> parent -> leftChild == temp){
            temp -> parent -> leftChild = temp -> leftChild;
          }
          else {
            temp -> parent -> rightChild = temp -> leftChild;
          }
          temp -> leftChild -> parent = temp -> parent;
        } else{
          MovieNode * x =temp -> rightChild;
          if (temp -> parent -> rightChild == temp){
            temp -> parent -> rightChild = x;
          }
          else {
            temp -> parent -> leftChild = x;
          }
          x -> parent = temp -> parent;
          delete temp;
          break;
        }
      }
    }
    
    else if (temp -> title.compare(title) > 0){
      temp = temp -> leftChild;
    }
    else{
      temp = temp -> rightChild;
    }
  }
  
  if (temp == nil){
    cout << "Movie not found." << endl;
  }
}

void MovieTree::leftRotate(MovieNode * x){
  MovieNode * y = x -> rightChild;
  x -> rightChild = y -> leftChild;
  if (y -> leftChild != nil){
    y -> leftChild -> parent = x;
  }
  y -> parent = x -> parent;
  if (x -> parent == nil){
    root = y;
  } else {
    if (x == x -> parent -> leftChild){
      x -> parent -> leftChild = y;
    } else {
      x -> parent -> rightChild = y;
    }
  }
  y -> leftChild = x;
  x -> parent = y;
}

void MovieTree::rightRotate(MovieNode * x){
  MovieNode * y = x -> leftChild;
  x -> leftChild = y -> rightChild;
  if (y -> rightChild != nil) {
    y -> rightChild -> parent = x;
  }
  y -> parent = x -> parent;
  
  if (x -> parent == nil) {
    root = y;
  } else {
    if (x == x -> parent -> leftChild){
      x -> parent -> leftChild = y;
    } else {
      x -> parent -> rightChild = y;
    }
  }
  y -> rightChild = x;
  x -> parent = y;
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){
  MovieNode * toAdd = new MovieNode(ranking, title, releaseYear, quantity);
  MovieNode * temp = root;
  MovieNode * parent = nil;

  if (root == nil){
    root = toAdd;
    root -> leftChild = nil;
    root -> rightChild = nil;
  } else {
    while (temp != nil){
      parent = temp;
      if ((parent -> title).compare(toAdd -> title)> 0){
        temp = temp -> leftChild;
      } else {
        temp = temp -> rightChild;
      }
    }

    if ((parent -> title).compare(toAdd -> title)> 0){
      parent -> leftChild = toAdd;
      toAdd -> parent = parent;
    } else {
      parent -> rightChild = toAdd;
      toAdd -> parent = parent;
    }

    toAdd -> leftChild = nil;
    toAdd -> rightChild = nil;
  }

  // red-black balancing
  while ((toAdd != root)and (toAdd -> parent -> isRed)){
    if (toAdd -> parent == toAdd -> parent -> parent -> leftChild){
      MovieNode * uncle = toAdd -> parent -> parent -> rightChild;
      if (uncle -> isRed){
        toAdd -> parent-> isRed = false;
        uncle -> isRed = false;
        toAdd -> parent -> parent -> isRed = true;
        toAdd = toAdd -> parent -> parent;
      } else {
        if (toAdd == toAdd -> parent -> rightChild){
          toAdd = toAdd -> parent;
          leftRotate(toAdd);
        }
        toAdd -> parent -> isRed = false;
        toAdd -> parent -> parent -> isRed = true;
        rightRotate(toAdd -> parent -> parent);
      }
    } else {
      MovieNode * uncle = toAdd -> parent -> parent -> leftChild;
      if (uncle -> isRed){
        toAdd -> parent -> isRed = false;
        uncle -> isRed = false;
        toAdd -> parent -> parent -> isRed = true;
        toAdd = toAdd -> parent -> parent;
      } else {
        if (toAdd == toAdd -> parent -> leftChild){
          toAdd = toAdd -> parent;
          rightRotate(toAdd);
        }
        toAdd -> parent -> isRed = false;
        toAdd -> parent -> parent -> isRed = true;
        leftRotate(toAdd -> parent -> parent);
      }
    }
  }
  root -> isRed = false;
  root -> parent = nil;
}

void MovieTree::findMovie(string title){
  bool found = false;
  MovieNode * temp = root;
  while (temp != nil){
    if ((temp -> title).compare(title)> 0){
      temp = temp -> leftChild;
    } else if ((temp -> title).compare(title)< 0){
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

  if (!found){
    cout << "Movie not found." << endl;
  }
}

void MovieTree::rentMovie(string title){
  bool found = false;
  MovieNode * temp = root;
  while (temp != nil){
    if (temp -> title.compare(title)> 0){
      temp = temp -> leftChild;
    } else if (temp -> title.compare(title)< 0){
      temp = temp -> rightChild;
    } else {
      found = true;
      if (temp -> quantity > 0){
        temp -> quantity = temp -> quantity - 1;
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << temp->ranking << endl; //info
        cout << "Title:" << temp->title << endl;
        cout << "Year:" << temp->year << endl;
        cout << "Quantity:" << temp->quantity << endl;
        if (temp -> quantity == 0){
          deleteMovieNode(temp -> title);
        }
      } else {
        cout << "Movie out of stock." << endl;
      }

      break;
    }
  }

  if (!found){
    cout << "Movie not found." << endl;
  }
}

void MovieTree::DeleteAll(MovieNode * node){
  if (node -> leftChild != nil){
    DeleteAll(node -> leftChild);
  }

  if (node -> rightChild != nil){
     DeleteAll(node -> rightChild);
  }

  cout << "Deleting: " << node -> title << endl;
  delete node;
}

MovieNode* search(string title){

}

MovieNode* searchRecursive(MovieNode * node, string value){

}

MovieNode* treeMinimum(MovieNode *node){

}


