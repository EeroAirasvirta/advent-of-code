#include <iostream>
#include <map>
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

    auto twos{0};
    auto threes{0};

    std::string line;
    while (std::getline(istream, line) ) {
        std::map<char, size_t> characters;
        for (const auto character : line) {
            ++characters[character];
        }

        bool twosFound{false};
        bool threesFound{false};
        for (const auto& it : characters) {
            if (!twosFound && it.second == 2) {
                ++twos;
                twosFound = true;
            }

            if (!threesFound && it.second == 3) {
                ++threes;
                threesFound = true;
            }

            if (twosFound && threesFound) {
                break;
            }
        }
    }

    std::cout << "twos: " << twos << std::endl;
    std::cout << "threes: " << threes << std::endl;
    std::cout << "checksum: " << twos*threes << std::endl;

    return 0;
}
