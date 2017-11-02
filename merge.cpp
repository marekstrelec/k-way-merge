#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <functional>

template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;


int merge() {
  std::string line;
  std::vector<std::unique_ptr<std::ifstream>> ifiles;
  min_heap<std::pair<std::string, int>> sheap;

  // open all files
  while (std::getline(std::cin, line)) {
    std::ifstream *iff = new std::ifstream(line);
    if (iff->is_open()) {
      ifiles.push_back(std::unique_ptr<std::ifstream>(iff));
    }
  }

  // fill
  for (int i = 0; i < ifiles.size(); ++i) {
    while (std::getline(*ifiles.at(i), line) && line.length() == 0);
    if (!ifiles.at(i)->eof()) {
      sheap.push(std::make_pair(line, i));
    }
  }

  // sort
  while (sheap.size() > 0) {
    std::string text = sheap.top().first;
    int pos = sheap.top().second;
    sheap.pop();

    std::cout << text << '\n';

    while (std::getline(*ifiles.at(pos), line) && line.length() == 0);
    if (!ifiles.at(pos)->eof()) {
      sheap.push(std::make_pair(line, pos));
    }
  }
}


int main() {
  merge();

  return 0;
}