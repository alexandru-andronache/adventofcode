#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2021_day10 {
    struct match {
        char begin;
        char end;
        int score;
    };

    int processCorruptString(std::string_view line) {
        std::string str;
        std::vector<match> braces{{'(', ')', 3},
                                  {'[', ']', 57},
                                  {'{', '}', 1197},
                                  {'<', '>', 25137}};
        for (const auto& c : line) {
            auto start = std::find_if(braces.begin(), braces.end(), [c](const auto& x) {
                return x.begin == c;
            });
            if (start != braces.end()) {
                str += c;
            }
            else {
                auto it = std::find_if(braces.begin(), braces.end(), [c](const auto& x) {
                    return x.end == c;
                });
                if (str.back() == it->begin) {
                    str.pop_back();
                }
                else {
                    return it->score;
                }
            }
        }
        return 0;
    }

    unsigned long long processIncompleteString(std::string_view line) {
        std::string str;
        std::vector<match> braces{{'(', ')', 1},
                                  {'[', ']', 2},
                                  {'{', '}', 3},
                                  {'<', '>', 4}};
        for (const auto& c : line) {
            auto start = std::find_if(braces.begin(), braces.end(), [c](const auto& x) {
                return x.begin == c;
            });
            if (start != braces.end()) {
                str += c;
            }
            else {
                str.pop_back();
            }
        }

        unsigned long long score = 0;
        for (int i = str.size() - 1; i >= 0; --i) {
            auto start = std::find_if(braces.begin(), braces.end(), [str, i](const auto& x) {
                return x.begin == str[i];
            });
            score = score * 5 + start->score;
        }
        return score;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        unsigned long long sum = 0;
        for (const auto & line : input) {
            sum += processCorruptString(line);
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<unsigned long long> scores;
        for (const auto & line : input) {
            if (!processCorruptString(line)) {
                scores.push_back(processIncompleteString(line));
            }
        }
        std::sort(scores.begin(), scores.end());
        return scores[scores.size() / 2];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day10::part_1("../2021/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day10::part_2("../2021/day10/input.in") << std::endl;

    return 0;
}
#endif
