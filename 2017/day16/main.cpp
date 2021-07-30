#include "file.h"
#include <iostream>
#include <deque>
#include <map>

namespace aoc2017_day16 {
    std::string part_1(std::string_view path, int size = 16) {
        std::string input = file::readFileAsString(path);
        std::deque<char> letters;
        for (int i = 0; i < size; ++i) {
            letters.push_back(i + 'a');
        }
        int i = 0;
        while (i < input.size()) {
            if (input[i] == 's') {
                i++;
                int nr = 0;
                while (input[i] != ',') {
                    nr = nr * 10 + input[i] - '0';
                    i++;
                }
                i++;
                for (int j = 0; j < nr; ++j) {
                    letters.push_front(letters.back());
                    letters.pop_back();
                }
            }
            else if (input[i] == 'p') {
                int nr1 = 0, nr2 = 0;
                for (int j = 0; j < letters.size(); ++j) {
                    if (letters[j] == input[i + 1]) nr1 = j;
                    if (letters[j] == input[i + 3]) nr2 = j;
                }
                std::swap(letters[nr1], letters[nr2]);
                i = i + 5;
            }
            else {
                i++;
                int nr1 = 0, nr2 = 0;
                while (input[i] != '/') {
                    nr1 = nr1 * 10 + input[i] - '0';
                    i++;
                }
                i++;
                while (i < input.size() && input[i] != ',') {
                    nr2 = nr2 * 10 + input[i] - '0';
                    i++;
                }
                i++;
                std::swap(letters[nr1], letters[nr2]);
            }
        }
        return std::string(letters.begin(), letters.end());
    }

    std::string part_2(std::string_view path, int size = 16) {
        constexpr int ROUNDS = 1000000000;
        std::map<std::string, int> rounds;
        std::deque<char> letters;

        std::string input = file::readFileAsString(path);
        for (int i = 0; i < size; ++i) {
            letters.push_back(i + 'a');
        }
        for (int k = 0; k < ROUNDS; ++k) {
            int i = 0;
            while (i < input.size()) {
                if (input[i] == 's') {
                    i++;
                    int nr = 0;
                    while (input[i] != ',') {
                        nr = nr * 10 + input[i] - '0';
                        i++;
                    }
                    i++;
                    for (int j = 0; j < nr; ++j) {
                        letters.push_front(letters.back());
                        letters.pop_back();
                    }
                } else if (input[i] == 'p') {
                    int nr1 = 0, nr2 = 0;
                    for (int j = 0; j < letters.size(); ++j) {
                        if (letters[j] == input[i + 1]) nr1 = j;
                        if (letters[j] == input[i + 3]) nr2 = j;
                    }
                    std::swap(letters[nr1], letters[nr2]);
                    i = i + 5;
                } else {
                    i++;
                    int nr1 = 0, nr2 = 0;
                    while (input[i] != '/') {
                        nr1 = nr1 * 10 + input[i] - '0';
                        i++;
                    }
                    i++;
                    while (i < input.size() && input[i] != ',') {
                        nr2 = nr2 * 10 + input[i] - '0';
                        i++;
                    }
                    i++;
                    std::swap(letters[nr1], letters[nr2]);
                }
            }

            auto el = rounds.find(std::string(letters.begin(), letters.end()));
            if (el == rounds.end()) {
                rounds.insert({std::string(letters.begin(), letters.end()), k});
            }
            else {
                int interval = k - el->second;
                while (k + interval < ROUNDS) {
                    k += interval;
                }
            }
        }
        return std::string(letters.begin(), letters.end());
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day16::part_1("../2017/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day16::part_2("../2017/day16/input.in") << std::endl;

    return 0;
}
#endif
