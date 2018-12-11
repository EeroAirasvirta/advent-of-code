#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Claim {
  std::string id;
  int xMin;
  int yMin;
  int xMax;
  int yMax;
  bool overlapping;

  bool overlaps(const Claim& other) const {
    return
        (xMin < other.xMax) && (xMax > other.xMin) &&
        (yMin < other.yMax) && (yMax > other.yMin);
  }
};

void parseInputRow(const std::string& row, Claim& claim);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream istream(filename);

  std::vector<Claim> claims;
  std::string line;
  while (std::getline(istream, line) ) {
    Claim claim;
    parseInputRow(line, claim);
    claims.push_back(claim);
  }
  istream.close();

  for (auto i = 0u; i < claims.size() - 1; ++i) {
    Claim& c1 = claims.at(i);

    for (auto j = i+1; j < claims.size(); ++j) {
      Claim& c2 = claims.at(j);
      if(c1.overlaps(c2)) {
        c1.overlapping = true;
        c2.overlapping = true;
      }
    }
  }

  for (auto claim : claims) {
    if (!claim.overlapping) {
      std::cout << claim.id << std::endl;
    }
  }

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

  claim.id = row.substr(1, atPos-1);
  claim.xMin = std::stoi(xMin);
  claim.yMin = std::stoi(yMin);
  claim.xMax = claim.xMin + std::stoi(width);
  claim.yMax = claim.yMin + std::stoi(height);
  claim.overlapping = false;
}
