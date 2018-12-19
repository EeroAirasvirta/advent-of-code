#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

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

  std::vector<std::vector<int>> grid(
    maxY+1, std::vector<int>(maxX+1, 0));

  std::map<int, int> sizes;

  for (auto y = 0u; y <= maxY; ++y) {
    for (auto x = 0u; x <= maxX; ++x) {
      unsigned int minDistance{0};
      int id{-1};

      for (auto i = 0u; i < coordinates.size(); ++i) {
        const auto& coordinate = coordinates.at(i);
        auto distance =
          std::abs(static_cast<int>(y-coordinate.second)) +
          std::abs(static_cast<int>(x-coordinate.first));
        if (id == -1) {
          minDistance = distance;
          id = i;
        } else if (distance < minDistance) {
          minDistance = distance;
          id = i;
        } else if (distance == minDistance) {
          id = -2;
        }
      }
      grid.at(y).at(x) = id;
      if (id >= 0) {
        sizes[id]++;
      }
    }
  }

  for (auto y = 0u; y <= maxY; ++y) {
    sizes.erase(grid.at(y).at(0));
    sizes.erase(grid.at(y).at(maxX));
  }

  for (auto x = 0u; x <= maxX; ++x) {
    sizes.erase(grid.at(0).at(x));
    sizes.erase(grid.at(maxY).at(x));
  }

  int maxSize{0};
  int maxId{0};

  for (auto size : sizes) {
    if (size.second > maxSize) {
      maxId = size.first;
      maxSize = size.second;
    }
  }

  std::cout << maxSize << std::endl;

  return 0;
}
