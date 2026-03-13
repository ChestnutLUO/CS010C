#ifndef GRAPH_ADJACENCY_LISTS_H_
#define GRAPH_ADJACENCY_LISTS_H_

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

class Graph {
  // Generic Graph API
 public:
  // Create empty graph with V vertices
  Graph(int V);
  // Create graph from input stream
  Graph(std::ifstream& ifs);
  // Add an edge v-w
  void AddEdge(int v, int w);
  // Vertices adjacent to v
  std::vector<int> Adj(int v);
  // Number of vertices
  int V();
  // Number of edges
  int E();

 private:
  // Adjacency lists implementation
  std::vector<std::vector<int>> adj_l;
  int nv;
  int ne = 0;
};

Graph::Graph(int V) : adj_l(V), nv(V) {
}

Graph::Graph(std::ifstream& ifs) {
  // Get number of vertices
  ifs >> nv;

  // Allocate lists of vertices
  adj_l.resize(nv);

  // Go through all the edges
  int v, w;
  while (ifs >> v >> w)
    AddEdge(v, w);
}

void Graph::AddEdge(int v, int w) {
  adj_l[v].push_back(w);
  ++ne;
}

std::vector<int> Graph::Adj(int v) {
  return adj_l[v];
}

int Graph::V() {
  return nv;
}
int Graph::E() {
  return ne;
}

#endif  // GRAPH_ADJACENCY_LISTS_H_
