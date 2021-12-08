#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day08 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, "|");
            std::vector<std::string> words = utils::splitString(tokens[1], " ");
            sol += std::count_if(words.begin(), words.end(), [](const auto& l) {
                return l.size() == 2 || l.size() == 3 || l.size() == 4 || l.size() == 7;
            });
        }
        return sol;
    }

    char getMissingLetter(std::string_view str, const std::vector<char>& letters) {
        for (const auto& l : str) {
            if (std::find(letters.begin(), letters.end(), l) == letters.end()) {
                return l;
            }
        }
        return ' ';
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sum = 0;

        for (const auto& line : input) {
            std::vector<std::string> words = utils::splitString(line, " |");
            // find 1
            char topRight = 'x', bottomRight = 'x', middle = 'x', top = 'x', bottom = 'x', topLeft = 'x', bottomLeft = 'x';
            for (const auto& w : words) {
                if (w.size() == 2) {
                    topRight = w[0];
                    bottomRight = w[1];
                }
            }

            // find 7
            for (const auto& w : words) {
                if (w.size() == 3) {
                    top = getMissingLetter(w, {topRight, bottomRight});
                }
            }

            // find 3
            for (const auto& w : words) {
                if (w.size() == 5 &&
                    std::count(w.begin(), w.end(), topRight) == 1 &&
                    std::count(w.begin(), w.end(), bottomRight) == 1) {
                    for (const auto& l : w) {
                        if (l != topRight && l != bottomRight && l != top) {
                            if (middle != 'x') {
                                if (bottom == 'x') {
                                    bottom = l;
                                }
                            }
                            else {
                                middle = l;
                            }
                        }
                    }
                }
            }

            // find 4
            for (const auto& w : words) {
                if (w.size() == 4) {
                    for (const auto& l : w) {
                        if (l == middle) {
                            topLeft = getMissingLetter(w, {topRight, bottomRight, middle});
                        }
                        else if (l == bottom) {
                            std::swap(middle, bottom);
                            topLeft = getMissingLetter(w, {topRight, bottomRight, middle});
                        }
                    }
                }
            }

            // find 0
            for (const auto& w : words) {
                if (w.size() == 6) {
                    if (std::count(w.begin(), w.end(), middle) == 0) {
                        bottomLeft = getMissingLetter(w, {top, bottom, topRight, bottomRight, topLeft});
                    }
                }
            }

            // find 5
            for (const auto& w : words) {
                if (w.size() == 5) {
                    if (std::count(w.begin(), w.end(), topLeft) == 1) {
                        if (std::count(w.begin(), w.end(), topRight) == 1) {
                            std::swap(topRight, bottomRight);
                        }
                    }
                }
            }

            int nr = 0;
            for (int i = 10; i < words.size(); ++i) {
                if (words[i].size() == 2) { // nr 1
                    nr = nr * 10 + 1;
                }
                else if (words[i].size() == 3) { // nr 7
                    nr = nr * 10 + 7;
                }
                else if (words[i].size() == 4) { // 4
                    nr = nr * 10 + 4;
                }
                else if (words[i].size() == 5) { // 2, 3, 5
                    if (std::count(words[i].begin(), words[i].end(), topRight) == 1 &&
                        std::count(words[i].begin(), words[i].end(), bottomRight) == 1) { // 3
                        nr = nr * 10 + 3;
                    }
                    else if (std::count(words[i].begin(), words[i].end(), topRight) == 1 &&
                             std::count(words[i].begin(), words[i].end(), bottomLeft) == 1) { // 2
                        nr = nr * 10 + 2;
                    }
                    else { // 5
                        nr = nr * 10 + 5;
                    }
                }
                else if (words[i].size() == 6) { //0, 6, 9
                    if (std::count(words[i].begin(), words[i].end(), middle) == 0) { // 0
                        nr = nr * 10 + 0;
                    }
                    else if (std::count(words[i].begin(), words[i].end(), topRight) == 1) { // 9
                        nr = nr * 10 + 9;
                    }
                    else { //6
                        nr = nr * 10 + 6;
                    }
                }
                else if (words[i].size() == 7) { // 8
                    nr = nr * 10 + 8;
                }
            }
            sum += nr;

        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day08::part_1("../2021/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day08::part_2("../2021/day08/input.in") << std::endl;

    return 0;
}
#endif
