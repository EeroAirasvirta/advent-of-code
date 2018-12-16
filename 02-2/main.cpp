#include <fstream>
#include <iostream>
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

  for (auto i = 0u; i < ids.size() - 1 ; ++i) {
    const auto& str1 = ids.at(i);

    for (auto j = i+1; j < ids.size(); ++j) {
      const auto& str2 = ids.at(j);
      if (str1.length() != str2.length()) {
        break;
      }

      auto diffIndex{-1};
      auto differencies{0u};
      for (auto k = 0u; k < str1.length(); ++k) {
        if (str1.at(k) != str2.at(k)) {
          ++differencies;
          diffIndex = static_cast<int>(k);
        }
      }

      if (differencies == 1) {
        std::cout << str1.substr(0, diffIndex) << str1.substr(diffIndex+1, str1.length() - i - diffIndex) << std::endl;
        return 0;
      }
    }
  }

  return 0;
}
