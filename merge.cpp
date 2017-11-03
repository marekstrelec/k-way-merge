#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <getopt.h>
#include <functional>

template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;


void normal_merge(std::vector<std::unique_ptr<std::ifstream>> &ifiles, min_heap<std::pair<std::string, int>> &sheap) {
  std::string line;

  while (sheap.size() > 0) {
    std::string text = sheap.top().first;
    int pos = sheap.top().second;
    sheap.pop();

    std::cout << text << '\n';

    // push the next line to the heap
    while (std::getline(*ifiles.at(pos), line) && line.length() == 0);
    if (!ifiles.at(pos)->eof()) {
      sheap.push(std::make_pair(line, pos));
    }
  }
}

void accum_merge(std::vector<std::unique_ptr<std::ifstream>> &ifiles, min_heap<std::pair<std::string, int>> &sheap,
                 char delim) {
  bool first = true;
  std::string line = "";
  std::string pre = "";
  int value = 0;
  std::size_t found = 0;

  while (sheap.size() > 0) {
    std::string text = sheap.top().first;
    int pos = sheap.top().second;
    sheap.pop();

    found = text.rfind(delim);
    if (found != std::string::npos) {
      if (pre == text.substr(0, found)) {
        // the key matches => increment the accumulator
        value += std::stoi(text.substr(found, text.length() - found));

      } else {
        // flush the buffer
        if (first)
          first = false;
        else
          std::cout << pre << delim << value << '\n';

        // update values
        pre = text.substr(0, found);
        value = std::stoi(text.substr(found, text.length() - found));
      }
    }

    // push the next line to the heap
    while (std::getline(*ifiles.at(pos), line) && line.length() == 0);
    if (!ifiles.at(pos)->eof()) {
      sheap.push(std::make_pair(line, pos));
    }
  }

  // flush the buffer
  std::cout << pre << delim << value << '\n';

}


void merge(bool accumulator, char delim) {
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

  // fill up the heap with the first line of each file
  for (int i = 0; i < ifiles.size(); ++i) {
    while (std::getline(*ifiles.at(i), line) && line.length() == 0);
    if (!ifiles.at(i)->eof()) {
      sheap.push(std::make_pair(line, i));
    }
  }

  // merge
  if (accumulator) {
    accum_merge(ifiles, sheap, delim);
  } else {
    normal_merge(ifiles, sheap);
  }

}


void print_usage() {
  std::cout << "Usage:\n"
            << " -a \t\tAccumulate values of lines with the same key.\n"
            << " -d delim \tUse delim as the field delimiter character instead of the tab character.\n"
            << " -h \t\tDisplay this help and exit.\n"
            << std::endl;
}


int main(int argc, char *argv[]) {
  int option = 0;
  bool accumulator = false;
  char delim = '\t';

  while ((option = getopt(argc, argv, "had:")) != -1) {
    switch (option) {
      case 'h':
        print_usage();
        exit(EXIT_SUCCESS);
      case 'a':
        accumulator = true;
        break;
      case 'd':
        delim = optarg[0];
        break;
      default:
        print_usage();
        exit(EXIT_FAILURE);
    }
  }

  merge(accumulator, delim);

  return 0;
}