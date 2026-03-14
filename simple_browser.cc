#include "simple_browser.h"

#include <fstream>
#include <sstream>
#include <stack>

std::string SimpleBrowser::NormalizeUrl(const std::string& url) {
  std::string s = url;
  if (s.substr(0, 8) == "https://")
    s = s.substr(8);
  else if (s.substr(0, 7) == "http://")
    s = s.substr(7);

  size_t slash = s.find('/');
  std::string domain = (slash == std::string::npos) ? s : s.substr(0, slash);
  std::string path = (slash == std::string::npos) ? "" : s.substr(slash);

  std::stack<std::string> parts;
  std::stringstream ss(domain);
  std::string part;
  while (std::getline(ss, part, '.'))
    parts.push(part);
  std::string reversed_domain;
  while (!parts.empty()) {
    if (reversed_domain.size() > 0)
      reversed_domain += '.';
    reversed_domain += parts.top();
    parts.pop();
  }

  std::string result = reversed_domain + path;
  for (char& c : result)
    c = (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
  while (!result.empty() && result.back() == '/')
    result.pop_back();
  return result;
}

bool SimpleBrowser::LoadPage(const std::string& url) {
  words_.clear();
  urls_.clear();

  std::ifstream in(url);
  if (!in.is_open())
    return false;

  std::string last_nonempty_line;
  std::string line;
  while (std::getline(in, line)) {
    std::stringstream ls(line);
    std::string before, raw_url;
    std::getline(ls, before, '"');
    std::getline(ls, raw_url, '"');
    if (before.find("<a href=") != std::string::npos && !raw_url.empty()) {
      urls_.push_back(NormalizeUrl(raw_url));
    }
    if (!line.empty() && line != "</body>" && line != "</html>") {
      last_nonempty_line = line;
    }
  }
  in.close();

  std::stringstream ss(last_nonempty_line);
  std::string word;
  while (ss >> word) {
    for (char& c : word)
      c = (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
    words_.push_back(word);
  }

  return true;
}
