//  External sorting implementation using two-phase merge sort:

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

//  Node structure for the min-heap used in k-way merge
struct HeapNode {
  int value;
  int file_index;

  bool operator>(const HeapNode &other) const { return value > other.value; }
};

//  orted in memory
void CreateInitialRuns(const std::string &infilename, const int num_ways,
                       const int run_size) {
  std::ifstream ifs(infilename);
  if (!ifs.is_open()) {
    std::cerr << "Error: Cannot open input file " << infilename << '\n';
    return;
  }
  int runs = 0;
  while (runs < num_ways) {
    std::vector<int> buffer;
    int value;
    for (int i = 0; i < run_size && ifs >> value; ++i) {
      buffer.push_back(value);
    }

    if (buffer.empty())
      break;

    //  Sort the current run in memory
    std::sort(buffer.begin(), buffer.end());

    //  Write sorted run to temporary file
    std::string temp_filename = infilename + "." + std::to_string(runs);
    std::ofstream ofs(temp_filename);
    if (!ofs.is_open()) {
      std::cerr << "Error: Cannot create temporary file " << temp_filename
                << '\n';
      ifs.close();
      return;
    }
    for (int i = 0; i < buffer.size(); ++i) {
      ofs << buffer[i] << "\n";
    }
    ofs.close();

    ++runs;
  }
  ifs.close();
}

void KWayMerge(const std::string &infilename, const int num_ways) {
  std::vector<std::ifstream> input_files(num_ways);
  for (int i = 0; i < num_ways; ++i) {
    std::string temp_filename = infilename + "." + std::to_string(i);
    input_files[i].open(temp_filename);
    if (!input_files[i].is_open()) {
      std::cerr << "Error: Cannot open temporary file " << temp_filename
                << '\n';
      return;
    }
  }

  std::string output_filename = infilename + ".sorted";
  std::ofstream output_file(output_filename);
  if (!output_file.is_open()) {
    std::cerr << "Error: Cannot create output file " << output_filename << '\n';
    for (auto &file : input_files) {
      if (file.is_open())
        file.close();
    }
    return;
  }

  std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>>
      min_heap;

  //  Initialize heap with first value from each run
  for (int i = 0; i < num_ways; ++i) {
    int value;
    if (input_files[i] >> value) {
      HeapNode node;
      node.value = value;
      node.file_index = i;
      min_heap.push(node);
    }
  }

  //  Repeatedly extract minimum and refill from corresponding file
  while (!min_heap.empty()) {
    HeapNode top = min_heap.top();
    min_heap.pop();

    output_file << top.value << "\n";

    int next_value;
    if (input_files[top.file_index] >> next_value) {
      HeapNode node;
      node.value = next_value;
      node.file_index = top.file_index;
      min_heap.push(node);
    }
  }

  //  Close all input files explicitly
  for (auto &file : input_files) {
    if (file.is_open()) {
      file.close();
    }
  }

  output_file.close();
}

#ifndef NO_MAIN
int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "usage: ./external_sort <input_file>"
              << "<num_ways> <run_size>" << '\n';
    return 1;
  }

  std::string infilename{argv[1]};

  int num_ways = atoi(argv[2]);
  int run_size = atoi(argv[3]);

  CreateInitialRuns(infilename, num_ways, run_size);

  KWayMerge(infilename, num_ways);

  return 0;
}
#endif
