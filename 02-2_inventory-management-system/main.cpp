#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream istream(filename);

  std::string line;
  std::vector<std::string> ids;
  while (std::getline(istream, line) ) {
    ids.push_back(line);
  }
  istream.close();

  std::sort(ids.begin(), ids.end());

  for (auto i = 0u; i < ids.size() - 1 ; ++i) {
    const auto& str1 = ids.at(i);
    const auto& str2 = ids.at(i+1);
    if (str1.length() != str2.length()) {
      break;
    }

    for (auto j = 0u; j < str1.length(); ++j) {
      if (str1.at(j) != str2.at(j)) {
        if (str1.compare(j+1, str1.length() - 1 - j, str2, j+1, str2.length() - 1 - j) != 0) {
          break;
        }

        std::cout << str1.substr(0, j) << str1.substr(j+1, str1.length() - 1 -j) << std::endl;
        return 0;
      }
    }
  }

  return 0;
}
