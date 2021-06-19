#include "file.h"
#include "md5.h"
#include <iostream>

namespace aoc2016_day05 {
    std::string part_1(const std::string& input) {
        int k = 0;
        std::string sol;
        for (int i = 0; i < 8; ++i) {
            bool found = false;
            while (!found) {
                k++;
                std::string result = md5::calculateMD5(input + std::to_string(k));
                if (result.substr(0, 5) == "00000") {
                    sol += result[5];
                    found = true;
                }
            }
        }

        return sol;
    }

    std::string part_2(const std::string& input) {
        int k = 0;
        std::string sol ="gggggggg";
        for (int i = 0; i < 8; ++i) {
            bool found = false;
            while (!found) {
                k++;
                std::string result = md5::calculateMD5(input + std::to_string(k));
                if (result.substr(0, 5) == "00000") {
                    if (result[5] - '0' <= 7 && sol[result[5] - '0'] == 'g') {
                        sol[result[5] - '0'] = result[6];
                        found = true;
                    }
                    else {
                        found = false;
                    }
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day05::part_1("cxdnnyjw") << std::endl;
    std::cout << "Part 2: " << aoc2016_day05::part_2("cxdnnyjw") << std::endl;

    return 0;
}
#endif
