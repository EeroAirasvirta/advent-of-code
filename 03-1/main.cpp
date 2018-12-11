#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct Claim {
  int xMin;
  int yMin;
  int width;
  int height;
};

void parseInputRow(const std::string& row, Claim& claim);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream istream(filename);

  std::map<int, std::map<int, int>> area;

  std::string line;
  while (std::getline(istream, line) ) {
    Claim claim;
    parseInputRow(line, claim);

    for (int row = claim.yMin; row < claim.yMin + claim.height; ++row) {
      for (int col = claim.xMin; col < claim.xMin + claim.width; ++col) {
        area[row][col]++;
      }
    }
  }

  istream.close();

  int overlaps{0};

  std::map<int, std::map<int, int>>::iterator it;
  for (const auto& row : area) {
    for (const auto& col : row.second) {
      if (col.second > 1)
        overlaps++;
    }
  }

  std::cout << overlaps << std::endl;

  return 0;
}

void parseInputRow(const std::string& row, Claim& claim) {
  auto atPos = row.find("@");
  auto commaPos = row.find(",");
  auto colonPos = row.find(":");
  auto xPos = row.find("x");
  auto xMin = row.substr(atPos+2, commaPos-atPos-2);
  auto yMin = row.substr(commaPos+1, colonPos-commaPos-1);
  auto width = row.substr(colonPos+2, xPos-colonPos-2);
  auto height = row.substr(xPos+1);

  claim.xMin = std::stoi(xMin);
  claim.yMin = std::stoi(yMin);
  claim.width = std::stoi(width);
  claim.height = std::stoi(height);
}
