#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        return 1;
    }

    const std::string filename = argv[1];

    std::ifstream istream(filename);

    std::vector<int> freqChanges;

    std::string line;
    while (std::getline(istream, line) ) {
        freqChanges.push_back(std::stoi(line));
    }

    int currentFrequency{0};
    std::set<int> frequencies;
    frequencies.insert(0);

    size_t changeIndex{0};

    while(true) {
        currentFrequency += freqChanges.at(changeIndex++);
        if (changeIndex == freqChanges.size()) {
            changeIndex = 0;
        }

        auto resultIt = frequencies.insert(currentFrequency);
        if (!resultIt.second) {
            std::cout << currentFrequency << std::endl;
            break;
        }
    }

    return 0;
}
