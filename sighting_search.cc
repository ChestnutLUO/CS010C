#include <algorithm>
#include <chrono> // NOLINT (build/c++11)
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// TODO: Define your Sighting class here
// The class should store speed, brightness, and calculated signature
// Signature formula: ceil((speed * brightness) / 10)
// Include constructor, destructor, and necessary operators

// TODO: Implement linear search function
// int linearSearch(std::vector<Sighting> sightings, std::vector<int> signatures)

// TODO: Implement binary search function  
// int binarySearch(std::vector<Sighting> sorted_sightings, std::vector<int> signatures)


int main(int argc, char *argv[]) {
  // TODO: Check command line arguments

  // TODO: Open and validate input files

  // TODO: Read sighting data from file
  // Parse each line containing speed and brightness values
  // Create Sighting objects and store in vector

  // TODO: Read signature data from file
  // Parse each line containing signature values
  // Store in vector of integers

  // User prompt for search method
  std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
  char search_type;
  bool validSelection = false;

  // Input validation loop
  while (!validSelection) {
    std::cin >> search_type;
    if (search_type != 'l' && search_type != 'b') {
      std::cerr << "Incorrect choice" << std::endl;
    } else {
      validSelection = true;
    }
  }

  // TODO: Initialize timing variables
  // std::chrono::high_resolution_clock::time_point start;
  // start = std::chrono::high_resolution_clock::now();

  // TODO: Implement search logic based on user choice
  switch (search_type) {
    case 'l':
      // TODO: Call linear search function
      break;
    case 'b':
      // TODO: Sort sightings vector first
      // TODO: Call binary search function
      break;
  }

  // TODO: Calculate and display timing

  // TODO: Write result to output file

  // TODO: Close files and clean up

  return 0;
}
