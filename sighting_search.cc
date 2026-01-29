#include <algorithm>
#include <chrono>  // NOLINT (build/c++11)
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// TODO: Define your Sighting class here
// The class should store speed, brightness, and calculated signature
// Signature formula: ceil((speed * brightness) / 10)
// Include constructor, destructor, and necessary operators
class Sighting {
    int speed = 0;
    int brightness = 0;
    int signature = 0;

   public:
    Sighting(int speed = 0, int brightness = 0) : speed(speed), brightness(brightness) {
        this->signature = (std::ceil((speed * brightness) / 10));
    }

    ~Sighting() = default;
    int get_signature() const { return signature; }

    bool operator<(const Sighting& other) const {
        if (signature != other.signature) return signature < other.signature;
        return speed < other.speed;
    }

    friend std::ostream& operator<<(std::ostream& out, const Sighting& s) {
        out << "Sighting(speed=" << s.speed << ", brightness=" << s.brightness << ", signature=" << s.signature << ")";
        return out;
    }
};

// TODO: Implement linear search function
int linearSearch(const std::vector<Sighting> sightings, const std::vector<int> signatures) {
    int count = 0;
    for (auto target_sig : signatures) {
        bool found = false;
        for (auto sighting : sightings) {
            if (sighting.get_signature() == target_sig) {
                found = true;
                break;
            }
        }
        if (found) {
            count++;
        }
    }
    return count;
}

// TODO: Implement binary search function
int binarySearch(std::vector<Sighting> sorted_sightings, std::vector<int> signatures) { return 0; }

int main(int argc, char* argv[]) {
    // TODO: Check command line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <sighting_file.dat> <signature_file.dat> <result_file.dat>" << std::endl;
        exit(0);
    }

    // TODO: Open and validate input files
    std::ifstream in_sighting_file(argv[1]);
    if (!in_sighting_file.is_open()) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        exit(0);
    }

    std::ifstream in_signature_file(argv[2]);
    if (!in_signature_file.is_open()) {
        std::cerr << "Error: cannot open file " << argv[2] << std::endl;
        exit(0);
    }

    std::vector<Sighting> sighting_record;

    // TODO: Read sighting data from file
    // Parse each line containing speed and brightness values
    // Create Sighting objects and store in vector

    {
        int speed, brightness;
        while (in_sighting_file >> speed >> brightness) {
            sighting_record.push_back({speed, brightness});
        }
        in_sighting_file.close();
    }

    // TODO: Read signature data from file
    // Parse each line containing signature values
    // Store in vector of integers

    std::vector<int> signatures;
    {
        int in_signarure;
        while (in_signature_file >> in_signarure) {
            signatures.push_back(in_signarure);
        }
        in_sighting_file.close();
    }

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
    std::chrono::high_resolution_clock::time_point start;
    start = std::chrono::high_resolution_clock::now();
    int match_count = 0;

    // TODO: Implement search logic based on user choice
    switch (search_type) {
        case 'l':
            match_count = linearSearch(sighting_record, signatures);
            break;
        case 'b':
            std::sort(sighting_record.begin(), sighting_record.end());
            match_count = binarySearch(sighting_record, signatures);
            break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
    // TODO: Calculate and display timinga
    std::cout << "CPU time: " << elapsed_us << " microseconds";
    // TODO: Write result to output file
    std::ofstream result_file(argv[3]);
    if (!result_file.is_open()) {
        std::cerr << "Error: cannot open file " << argv[3] << "\n";
        return 1;
    }
    result_file << match_count << "\n";
    result_file.close();

    // TODO: Close files and clean up

    return 0;
}
