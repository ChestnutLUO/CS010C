#include "page_file.h"

PageFile PageFile::Read(std::ifstream& in) {
  PageFile pf;
  std::getline(in, pf.url);
  in >> pf.impact;
  in.ignore();
  int num_links;
  in >> num_links;
  in.ignore();
  for (int i = 0; i < num_links; i++) {
    long idx;
    in >> idx;
    in.ignore();
    pf.indices.push_back(idx);
  }
  return pf;
}

void PageFile::Write(std::ofstream& out) const {
  out << url << "\n";
  out << impact << "\n";
  out << indices.size() << "\n";
  for (long idx : indices) {
    out << idx << "\n";
  }
}
