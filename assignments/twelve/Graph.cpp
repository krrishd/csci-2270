#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include "Graph.h"

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
    v.district = -1;
    vertices.push_back(v);
  }
}

template<class T>
void Graph<T>::displayEdges() {
  //loop through all vertices and adjacent vertices
  for (int i = 0; i < vertices.size(); i++){
    cout << vertices[i].district << ":" << vertices[i].name << "-->";
    for (int j = 0; j < vertices[i].adj.size(); j++){
      cout << vertices[i].adj[j].v->name;
      if (j != vertices[i].adj.size() - 1) {
        cout << "***";
      }
    }
    cout << endl;
  }
}

template<class T>
void Graph<T>::assignDistricts() {
  int district = 1;
  for(int i = 0; i < vertices.size(); i++) {
    if (vertices[i].district == -1) {
      BFTraversalLabel(vertices[i].name, district);
      district++;
    }
  }
}

template<class T>
void Graph<T>::BFTraversalLabel(T startingCity, int distID) {
  queue<vertex<string>*> q;

  for (int i = 0; i < vertices.size(); i++) {
    vertices[i].visited = false;
  }
    
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i].name == startingCity) {
      vertices[i].visited = true;
      q.push(&vertices[i]);
      vertices[i].district = distID;
      break;
    }
  }

  while (q.empty() != true) {
    vertex<string> * front = q.front();
    q.pop();
    for (int i = 0; i < front -> adj.size(); i++) {
      if (front -> adj[i].v -> visited == false) {
        front -> adj[i].v -> visited = true;
        front -> adj[i].v -> district = distID;
        q.push(front -> adj[i].v);
      }
    }
  }
}

template<class T>
void Graph<T>::shortestPath(T startingCity,T endingCity) {
  vertex<string> * start = findVertex(startingCity); 
  vertex<string> * end = findVertex(endingCity);

  if (start == NULL or end == NULL) {
    cout << "One or more cities doesn't exist" << endl;
    return;
  }
  
  if (end -> district != start -> district) {
    cout << "No safe path between cities" << endl;
    return;
  }

  if (end->district == -1 || start->district == -1) {
    cout << "Please identify the districts before checking distances" << endl;
    return;
  }

  for(int i = 0; i < vertices.size(); i++) {
    vertices[i].visited = false;
  }
        
  start -> visited = true;
  queueVertex<string> v;
  v.distance = 0;
  v.path.push_back(start);
  queue<queueVertex<string> > q;
  q.push(v);

  while (q.empty() != true) {
    v = q.front();
    q.pop();

    for(int i = 0; i < v.path.back()->adj.size(); i++) {
      if (v.path.back()->adj[i].v->visited == false) {
        vector<vertex<string> *> path = v.path;
        v.path.back()->adj[i].v->visited = true;
        int distance = v.distance + 1;

        path.push_back(v.path.back()->adj[i].v);
        queueVertex<string> temp;
        temp.path = path;
        temp.distance = distance;

        if (v.path.back()->adj[i].v == end) {
          cout << temp.distance;
          for (int j = 0; j < temp.path.size(); j++) {
            cout << "," << temp.path[j]->name;
          }
          cout << endl;
          return;
        }
        else {
          q.push(temp);
        }
      }
    }
  }
  return;
}

template<class T>
vertex<T> * Graph<T>::findVertex(T name) {
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i].name == name) {
      return &vertices[i];
    }
  }
  return NULL;
}

template<class T>
void Graph<T>::populateWithFileContents(char* filename){
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