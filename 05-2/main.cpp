#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

constexpr char FIRST_CHAR{65};
constexpr char LAST_CHAR{90};
constexpr char CASE_DIFFERENCE{32};

void react(std::string& polymer, char unit);

bool checkPolarity(char first, char second);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);

  std::string tempResult;
  char nextUnit;
  while (file.get(nextUnit)) {
    react(tempResult, nextUnit);
  }
  file.close();

  auto minLength{tempResult.length()};
  for (auto i = FIRST_CHAR; i <= LAST_CHAR ; ++i) {
    std::string result;
    for (auto j = 0u ; j < tempResult.length(); ++j) {
      nextUnit = tempResult.at(j);
      if (nextUnit == i || nextUnit == i + CASE_DIFFERENCE) {
        continue;
      }
      react(result, nextUnit);
    }

    if (result.length() < minLength) {
      minLength = result.length();
    }
  }

  std::cout << minLength << std::endl;

  return 0;
}

void react(std::string& polymer, char unit)
{
  if (!isalpha(unit)) {
    return;
  }
  polymer.push_back(unit);
  while (polymer.length() > 1 && checkPolarity(
           polymer.at(polymer.length()-2), polymer.at(polymer.length()-1))) {
    polymer.pop_back();
    polymer.pop_back();
  }
}

bool checkPolarity(char first, char second)
{
  return (first != second && tolower(first) == tolower(second));
}
