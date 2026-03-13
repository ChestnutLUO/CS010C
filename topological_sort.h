#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include <queue>
#include <vector>

#include "graph.h"

class TopologicalSort {
 public:
  // Perform topological sort on @G
  TopologicalSort(Graph G);
  // Return true if at least one linear ordering exists
  bool HasOrdering();
  // Return possible linear ordering of all vertices
  std::vector<int> GetOrdering();

 private:
  // TODO (Q2.1): Add private data members
  // Hint: You need to track visited vertices, in-degrees, and the final
  // ordering
  std::vector<bool> visited;
  std::vector<int> indegrees;
  std::vector<int> order;
  // TODO (Q2.1): Implement helper functions
  void SetVisited(int v);
  bool IsVisited(int v);
  void FillInDegree(Graph G);

  // TODO (Q2.2): Implement the main algorithm
  std::vector<int> LinearOrdering(Graph G);
};

TopologicalSort::TopologicalSort(Graph G)
    : visited(G.V(), false), indegrees(G.V(), 0), order() {
  FillInDegree(G);
  LinearOrdering(G);
}
// TODO (Q2.3): Implement the constructor
// It should:
// 1. Initialize visited vector (all false)
// 2. Initialize indegree vector (all 0)
// 3. Call FillInDegree to compute in-degrees
// 4. Call LinearOrdering to perform topological sort

bool TopologicalSort::HasOrdering() {
  return !order.empty();
}

// TODO (Q2.3): Implement HasOrdering()
// Return true if order is not empty

std::vector<int> TopologicalSort::GetOrdering() {
  if (!HasOrdering()) {
    throw std::runtime_error("Graph has a cycle");
  }
  return order;
}
// TODO (Q2.3): Implement GetOrdering()
// Throw an exception if there's no ordering (graph has a cycle)
// Otherwise return the order vector

void TopologicalSort::SetVisited(int v) {
  visited.at(v) = true;
}
// TODO (Q2.1): Implement SetVisited(int v)
// Mark vertex v as visited

bool TopologicalSort::IsVisited(int v) {
  return visited.at(v);
}
// TODO (Q2.1): Implement IsVisited(int v)
// Return whether vertex v has been visited

void TopologicalSort::FillInDegree(Graph G) {
  for (int v = 0; v < G.V(); v++) {
    for (auto w : G.Adj(v)) {
      indegrees.at(w)++;
    }
  }
}
// TODO (Q2.1): Implement FillInDegree(Graph G)
// For each vertex v in G:
//   For each adjacent vertex w of v:
//     Increment indegree[w]

// TODO (Q2.2): Implement LinearOrdering(Graph G)
// 1. Create a queue and a sequence vector
// 2. Find all vertices with in-degree 0 and add them to queue
// 3. While queue is not empty:
//    a. Dequeue a vertex and add it to sequence
//    b. For each adjacent vertex:
//       - Decrement its in-degree
//       - If in-degree becomes 0, add to queue
// 4. If sequence size != number of vertices, return empty vector (cycle
// detected)
// 5. Otherwise return sequence
std::vector<int> TopologicalSort::LinearOrdering(Graph G) {
  std::queue<int> q;
  std::vector<int> sequence;

  for (int v = 0; v < G.V(); v++) {
    if (indegrees.at(v) == 0)
      q.push(v);
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    SetVisited(v);
    sequence.push_back(v);
    for (auto w : G.Adj(v)) {
      if (--indegrees.at(w) == 0)
        q.push(w);
    }
  }

  if (sequence.size() != G.V())
    return {};
  order = sequence;
  return sequence;
}

// TODO (Q2.4): What is the time complexity of this algorithm?
// Answer: O(E+V)

#endif  // TOPOLOGICAL_SORT_H
