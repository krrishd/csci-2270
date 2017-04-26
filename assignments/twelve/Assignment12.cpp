#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

int getMenuInput() {
  string userInput;

  cout << "======Main Menu======" << endl;
  cout << "1. Print vertices" << endl;
  cout << "2. Find districts" << endl;
  cout << "3. Find shortest path" << endl;
  cout << "4. Quit" << endl;
  
  getline(cin, userInput);
  return stoi(userInput);
}

int main() {
    Graph<string> g;
    g.populateWithFileContents("zombieCities.txt");
    g.displayEdges();
    /*g.addVertex("Boulder");
    g.addVertex("Denver");
    g.addVertex("New Mexico");
    g.addVertex("Texas");
    g.addVertex("New Orleans");
    //edge written to be undirected
    g.addEdge("Boulder", "Denver", 30);
    g.addEdge("Boulder", "New Mexico", 200);
    g.addEdge("Boulder", "Texas", 500);
    g.addEdge("Denver", "Texas", 300);
    g.addEdge("Texas", "New Orleans", 500);
    g.displayEdges();

    /*
    Graph<int> g2;
    g2.addVertex(5);
    g2.addVertex(6);
    g2.addVertex(7);
    g2.addVertex(8);
    g2.addEdge(5,6,30);
    g2.addEdge(5,7,300);
    g2.addEdge(7,8,10);
    g2.displayEdges();
    return 0;*/
}