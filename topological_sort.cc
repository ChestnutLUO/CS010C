#include <fstream>

#include "topological_sort.h"

int main(int argc, char *argv[]) {
    // CLI args
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0]
            << " <graph.txt>" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);

    // build graph representation
    Graph G(ifs);

    // run topological sort and display result
    TopologicalSort topologicalSort(G);

    if (topologicalSort.HasOrdering()) {
        std::cout << "possible order: ";

        for (auto v : topologicalSort.GetOrdering()) {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    } else {
        std::cout << "No ordering found." << std::endl;
    }

    return 0;
}
