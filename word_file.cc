#include "word_file.h"

WordFile WordFile::Read(std::ifstream& in) {
  WordFile wf;
  std::getline(in, wf.word);
  int num_pages;
  in >> num_pages;
  in.ignore();
  for (int i = 0; i < num_pages; i++) {
    long idx;
    in >> idx;
    in.ignore();
    wf.indices.push_back(idx);
  }
  return wf;
}

void WordFile::Write(std::ofstream& out) const {
  out << word << "\n";
  out << indices.size() << "\n";
  for (long idx : indices) {
    out << idx << "\n";
  }
}
