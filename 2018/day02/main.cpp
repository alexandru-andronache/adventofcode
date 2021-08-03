#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2018_day02 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int letter2 = 0, letter3 = 0;
        for (const auto& word : input) {
            std::vector<int> letters(26, 0);
            bool isLetter2 = false, isLetter3 = false;
            for (const auto& letter : word) {
                letters[letter - 'a']++;
            }
            for (const auto& l : letters) {
                if (l == 2) isLetter2 = true;
                if (l == 3) isLetter3 = true;
            }
            if (isLetter2) letter2++;
            if (isLetter3) letter3++;
        }
        return letter2 * letter3;
    }

    std::string part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& word1 : input) {
            for (const auto& word2 : input) {
                if (word1.size() == word2.size()) {
                    std::string result;
                    int diff = 0;
                    for (int i = 0; i < word1.size(); ++i) {
                        if (word1[i] != word2[i]) {
                            diff++;
                        }
                        else {
                            result += word1[i];
                        }
                    }
                    if (diff == 1) {
                        return result;
                    }
                }
            }
        }
        return "";
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day02::part_1("../2018/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day02::part_2("../2018/day02/input.in") << std::endl;

    return 0;
}
#endif
