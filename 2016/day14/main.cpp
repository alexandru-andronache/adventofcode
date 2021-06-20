#include "file.h"
#include "utilities.h"
#include "md5.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2016_day14 {
    int part_1(const std::string& input, int steps = 64) {
        int index = 0;
        for (int i = 0; i < steps; ++i) {
            bool found = false;
            while (!found) {
                index++;
                std::string str = md5::calculateMD5(input + std::to_string(index));

                char c = 'z';
                for (int j = 0; j < str.size() - 2; ++j) {
                    if (str[j] == str[j + 1] &&
                    str[j] == str[j + 2] &&
                    c == 'z') {
                        c = str[j];
                    }
                }

                if (c != 'z') {
                    for (int j = index + 1; j <= index + 1000; ++j) {
                        std::string str = md5::calculateMD5(input + std::to_string(j));
                        bool isEqual = false;
                        for (int k = 0; k < str.size() - 5; ++k) {
                            if (str[k] == c) {
                                isEqual = true;
                                for (int p = 0; p < 5; ++p) {
                                    if (str[k + p] != c) {
                                        isEqual = false;
                                    }
                                }
                            }
                            if (isEqual) {
                                k = str.size();
                                j = index + 1000;
                                found = true;
                            }
                        }
                    }
                }
            }
        }

        return index;
    }

    int part_2(const std::string& input, int steps = 64, int hashings = 2016) {
        std::vector<std::string> hashes;
        for (int i = 0; i < 30000; ++i) {
//            std::cout << i << std::endl;
            std::string str = md5::calculateMD5(input + std::to_string(i));
            for (int j = 0; j < hashings; ++j) {
                str = md5::calculateMD5(str);
            }
            hashes.emplace_back(str);
        }

        int index = 0;
        for (int i = 0; i < steps; ++i) {
            bool found = false;
            while (!found) {
                index++;
                std::string str = hashes[index];

                char c = 'z';
                for (int j = 0; j < str.size() - 2; ++j) {
                    if (str[j] == str[j + 1] &&
                    str[j] == str[j + 2] &&
                    c == 'z') {
                        c = str[j];
                    }
                }

                if (c != 'z') {
                    for (int j = index + 1; j <= index + 1000; ++j) {
                        std::string str = hashes[j];
                        bool isEqual = false;
                        for (int k = 0; k < str.size() - 5; ++k) {
                            if (str[k] == c) {
                                isEqual = true;
                                for (int p = 0; p < 5; ++p) {
                                    if (str[k + p] != c) {
                                        isEqual = false;
                                    }
                                }
                            }
                            if (isEqual) {
                                k = str.size();
                                j = index + 1000;
                                found = true;
                            }
                        }
                    }
                }
            }
        }

        return index;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day14::part_1("cuanljph") << std::endl;
    std::cout << "Part 2: " << aoc2016_day14::part_2("cuanljph") << std::endl;

    return 0;
}
#endif
