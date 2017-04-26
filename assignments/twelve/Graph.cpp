#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Graph.hpp"

using namespace std;

template<class T>
Graph<T>::Graph() {

}

template<class T>
Graph<T>::~Graph() {

}

template<class T>
void Graph<T>::addEdge(T v1, T v2, int weight) {
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i].name == v1){
      for(int j = 0; j < vertices.size(); j++){
        if(vertices[j].name == v2 && i != j){
          adjVertex<T> av;
          av.v = &vertices[j];
          av.weight = weight;
          vertices[i].adj.push_back(av);

          //add edge in the other direction
          //vertices[i].adj.push_back(av);
          //another vertex for edge in other direction
          //adjVertex<T> av2;
          //av2.v = &vertices[i];
          //av2.weight = weight;
          //vertices[j].adj.push_back(av2);
        }
      }
    }
  }
}

template<class T>
void Graph<T>::addVertex(T name) {
  bool found = false;
  for (int i = 0; i < vertices.size(); i++){
    if(vertices[i].name == name){
      found = true;
      cout<<vertices[i].name<<" found."<<endl;
    }
  }
  
  if(found == false){
    vertex<T> v;
    v.name = name;
    vertices.push_back(v);
  }
}

template<class T>
void Graph<T>::displayEdges() {
  //loop through all vertices and adjacent vertices
  for (int i = 0; i < vertices.size(); i++){
    cout << vertices[i].name << "-->";
    for (int j = 0; j < vertices[i].adj.size(); j++){
      cout << vertices[i].adj[j].v->name << "***";
    }
    cout << endl;
  }
}

template<class T>
void Graph<T>::assignDistricts() {
  int currentDistrict = 1;
  for (int i = 0; i < vertices.size(); i++) {
    vertices[i].district = currentDistrict;
    for (int j = 0; j < vertices[i].adj.size(); j++) {
      vertices[i].adj[j].v -> district = currentDistrict;
    }
  }
}

template<class T>
void Graph<T>::BFTraversalLabel(T startingCity, int distID) {

}

template<class T>
void Graph<T>::shortestPath(T startingCity,T endingCity) {

}

template<class T>
vertex<T> * Graph<T>::findVertex(T name) {

}

template<class T>
void Graph<T>::populateWithFileContents(string filename){
  string data;
  string dataProcessed;
  map<int, string> columnIndex;
  bool onLabelRow = true;
  ifstream inFile(filename);


  while (getline(inFile, data)) {
    stringstream ss(data);
    int positionWithinRow = 0;
    string currentCity;
    while (getline(ss, dataProcessed, ',')) {
      // first row
      if (onLabelRow) {
        if (positionWithinRow != 0) {
          columnIndex[positionWithinRow] = dataProcessed;
          addVertex(dataProcessed);
        }
      } else { // every other row
        if (positionWithinRow == 0) {
          currentCity = dataProcessed;
        } else {
          if (stoi(dataProcessed) != -1) {
            addEdge(currentCity, columnIndex[positionWithinRow], stoi(dataProcessed));
          }
        }
      }
      positionWithinRow++;
    }
    positionWithinRow = 0;
    onLabelRow = false;
  }
}

template class Graph<string>;