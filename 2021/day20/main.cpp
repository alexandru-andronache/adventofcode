#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>

namespace aoc2021_day20 {
    int solve(std::string_view path, int steps) {
        const int N = 1000;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> map(N, std::vector<bool>(N, false));

        int middle = N / 2 - input[2].size() / 2;
        utils::point start {middle, middle};
        int size = input[2].size();

        for (int i = 2; i < input.size(); ++i) {
            for (int j = 0; j < input[i].size(); ++j) {
                map[start.x + i - 2][start.y + j] = (input[i][j] == '#');
            }
        }

        for (int step = 0; step < steps; ++step) {
            int newSol = 0;
            std::vector<std::vector<bool>> newMap(N, std::vector<bool>(N, false));
            start.x -= 1;
            start.y -= 1;
            size += 2;
            for (int x = start.x; x < start.x + size; ++x) {
                for (int y = start.y; y < start.y + size; ++y) {
                    std::bitset<9> mask;
                    int k = 0;
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            mask[8 - k] = map[x + i][y + j];
                            k++;
                        }
                    }
                    newMap[x][y] = input[0][mask.to_ulong()] == '#';
                    if (newMap[x][y]) {
                        newSol++;
                    }
                }
            }

            if (input[0][0] == '#') {
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        if (i < start.x || i >= start.x + size || j < start.y || j >= start.y + size) {
                            newMap[i][j] = (step % 2 == 0);
                        }
                    }
                }
            }
            map = newMap;
        }

        int sol = 0;
        for (const auto& line : map) {
            sol += std::count(line.begin(), line.end(), true);
        }

        return sol;
    }

    int part_1(std::string_view path) {
        return solve(path, 2);
    }

    int part_2(std::string_view path) {
        return solve(path, 50);
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day20::part_1("../2021/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day20::part_2("../2021/day20/input.in") << std::endl;

    return 0;
}
#endif
