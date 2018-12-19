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
  std::ifstream file(filename);

  std::vector<std::pair<int, int>> coordinates;
  std::string line;
  unsigned int maxX{0};
  unsigned int maxY{0};
  while (std::getline(file, line)) {
    auto commaPos = line.find(',');
    unsigned int x = std::stoi(line.substr(0, commaPos));
    unsigned int y = std::stoi(line.substr(commaPos + 2));
    if (x > maxX) {
      maxX = x;
    }
    if (y > maxY) {
      maxY = y;
    }
    coordinates.push_back({x, y});
  }
  file.close();

  int safePoints{0};
  for (auto y = 0u; y <= maxY; ++y) {
    for (auto x = 0u; x <= maxX; ++x) {
      int sumOfDistances{0};

      for (auto i = 0u; i < coordinates.size(); ++i) {
        const auto& coordinate = coordinates.at(i);
        auto distance =
          std::abs(static_cast<int>(y-coordinate.second)) +
          std::abs(static_cast<int>(x-coordinate.first));

        sumOfDistances += distance;
      }
      if (sumOfDistances < 10000) {
        safePoints++;
      }
    }
  }

  std::cout << safePoints << std::endl;

  return 0;
}
