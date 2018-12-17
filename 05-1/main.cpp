#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

bool checkPolarity(char first, char second);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);

  std::string result;
  char nextUnit;
  while (file.get(nextUnit)) {
    if (!isalpha(nextUnit)) {
      continue;
    }
    result.push_back(nextUnit);
    while (result.length() > 1 && checkPolarity(
             result.at(result.length()-2), result.at(result.length()-1))) {
      result.pop_back();
      result.pop_back();
    }
  }
  file.close();
  std::cout << result.length() << std::endl;

  return 0;
}

bool checkPolarity(char first, char second)
{
  return (first != second && tolower(first) == tolower(second));
}
