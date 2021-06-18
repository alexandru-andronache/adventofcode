#include "file.h"
#include "utilities.h"
#include "string_util.h"
#include <iostream>
#include <set>
#include <string>

namespace aoc2015_day19 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<std::string, std::string>> replacements;
        for (int i = 0; i < input.size() - 1; ++i) {
            std::vector<std::string> words = utils::splitString(input[i], " ");
            replacements.emplace_back(words[0], words[2]);
        }
        std::string str = *(input.end() - 1);

        std::set<std::string> results;

        for (const auto& r : replacements) {
            int i = 0;
            while (i + r.first.size() <= str.size()) {
                if (str.substr(i, r.first.size()) == r.first) {
                    std::string t = str;
                    t.replace(i, r.first.size(), r.second);
                    results.insert(t);
                }
                i++;
            }
        }

        return results.size();
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::string str = *(input.end() - 1);
        int total = 0;
        for (const auto& c : str) {
            total += (c >= 'A' && c <= 'Z');
        }

        return total - 2 * string::findNumberOfSubstrings(str, "Rn") - 2 * string::findNumberOfSubstrings(str, "Y") - 1;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day19::part_1("../2015/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day19::part_2("../2015/day19/input.in") << std::endl;

    return 0;
}
#endif
