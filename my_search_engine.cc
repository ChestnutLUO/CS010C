#include "my_search_engine.h"

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <utility>

long MySearchEngine::IndexPage(const std::string& url) {
  long index = page_disk_.NewFile();
  page_disk_.Put(index, PageFile(url));
  index_of_url_.Put(url, index);
  return index;
}

long MySearchEngine::IndexWord(const std::string& word) {
  long index = word_disk_.NewFile();
  word_disk_.Put(index, WordFile(word));
  index_of_word_[word] = index;
  return index;
}

void MySearchEngine::Collect(const std::vector<std::string>& starting_urls) {
  std::queue<long> queue;

  for (const std::string& url : starting_urls) {
    if (!index_of_url_.ContainsKey(url))
      queue.push(IndexPage(url));
  }

  while (!queue.empty()) {
    long page_idx = queue.front();
    queue.pop();

    std::string url = page_disk_.Get(page_idx).url;
    if (!browser_.LoadPage(url))
      continue;

    std::unordered_set<std::string> seen_urls;
    //  https://en.cppreference.com/w/cpp/container/unordered_set.html
    //  Separate Chaining Hash Table
    //  Worst O(N )

    for (const std::string& link : browser_.GetURLs()) {
      if (seen_urls.count(link))
        continue;
      seen_urls.insert(link);
      if (!index_of_url_.ContainsKey(link))
        queue.push(IndexPage(link));
      long link_idx = index_of_url_.Get(link);
      page_disk_.Get(page_idx).indices.push_back(link_idx);
    }

    std::unordered_set<std::string> seen_words;
    for (const std::string& word : browser_.GetWords()) {
      if (seen_words.count(word))
        continue;
      seen_words.insert(word);
      if (!index_of_word_.count(word))
        IndexWord(word);
      long word_idx = index_of_word_[word];
      word_disk_.Get(word_idx).indices.push_back(page_idx);
    }
  }
}

void MySearchEngine::RankIteration() {
  std::vector<long> indices = page_disk_.GetIndices();
  size_t total = indices.size();

  double zero_link_impact = 0.0;
  for (long idx : indices) {
    if (page_disk_.Get(idx).indices.empty())
      zero_link_impact += page_disk_.Get(idx).impact;
  }
  zero_link_impact /= total;

  for (long idx : indices) {
    const PageFile& page = page_disk_.Get(idx);
    if (page.indices.empty())
      continue;
    double share = page.impact / page.indices.size();
    for (long target : page.indices)
      page_disk_.Get(target).impact_temp += share;
  }

  for (long idx : indices) {
    PageFile& page = page_disk_.Get(idx);
    page.impact = page.impact_temp + zero_link_impact;
    page.impact_temp = 0.0;
  }
}

void MySearchEngine::Rank() {
  for (long idx : page_disk_.GetIndices()) {
    page_disk_.Get(idx).impact = 1.0;
    page_disk_.Get(idx).impact_temp = 0.0;
  }
  for (int i = 0; i < 20; i++)
    RankIteration();
}

bool MySearchEngine::AllEqual(const std::vector<long>& vec) const {
  for (size_t i = 1; i < vec.size(); i++)
    if (vec[i] != vec[0])
      return false;
  return true;
}

std::vector<std::string> MySearchEngine::Search(
    const std::vector<std::string>& search_words, int num_results) {
  std::vector<const std::vector<long>*> lists;
  for (const std::string& word : search_words) {
    if (!index_of_word_.count(word))
      return {};
    long widx = index_of_word_[word];
    lists.push_back(&word_disk_.Get(widx).indices);
  }

  std::vector<size_t> pos(lists.size(), 0);

  using Entry = std::pair<double, std::string>;
  std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> heap;

  bool flag = false;
  while (!flag) {
    for (size_t i = 0; i < lists.size(); i++) {
      if (pos[i] >= lists[i]->size()) {
        flag = true;
        break;
      }
    }
    if (flag)
      break;
    std::vector<long> cur(lists.size());
    for (size_t i = 0; i < lists.size(); i++)
      cur[i] = (*lists[i])[pos[i]];

    if (AllEqual(cur)) {
      long page_idx = cur[0];
      double impact = page_disk_.Get(page_idx).impact;
      std::string url = page_disk_.Get(page_idx).url;
      if (heap.size() < (size_t)(num_results)) {
        heap.push({impact, url});
      } else if (impact > heap.top().first) {
        heap.pop();
        heap.push({impact, url});
      }
      for (size_t i = 0; i < lists.size(); i++)
        pos[i]++;
    } else {
      long max_idx = *std::max_element(
          cur.begin(),
          cur.end());  //  https://en.cppreference.com/w/cpp/algorithm/max_element.html
      for (size_t i = 0; i < lists.size(); i++)
        if (cur[i] < max_idx)
          pos[i]++;
    }
  }
  std::vector<std::string> results(heap.size());
  for (int i = heap.size() - 1; i >= 0; i--) {
    results[i] = heap.top().second;
    heap.pop();
  }
  return results;
}
