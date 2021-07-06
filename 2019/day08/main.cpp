#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2019_day08 {
    int part_1(std::string_view path, int n = 25, int m = 6) {
        std::string str = file::readFileAsString(path);

        int k = 0;
        int min = std::numeric_limits<int>::max();
        int sol = 0;
        while (k < str.size()) {
            int nr0 = 0, nr1 = 0, nr2 = 0;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (str[k] == '0') nr0++;
                    if (str[k] == '1') nr1++;
                    if (str[k] == '2') nr2++;
                    k++;
                }
            }
            if (nr0 < min) {
                min = nr0;
                sol = nr1 * nr2;
            }
        }
        return sol;
    }

    void part_2(std::string_view path, int n = 25, int m = 6) {
        std::string str = file::readFileAsString(path);

        std::vector<std::vector<int>> a(m, std::vector<int>(n, -1));

        int k = 0;
        while (k < str.size()) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (a[i][j] == -1 && str[k] != '2') a[i][j] = str[k] - '0';
                    k++;
                }
            }
        }

        std::cout << std::endl;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j] == 1) std::cout << "1";
                else std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day08::part_1("../2019/day08/input.in") << std::endl;
    std::cout << "Part 2: " << std::endl;
    aoc2019_day08::part_2("../2019/day08/input.in");

    return 0;
}
#endif
