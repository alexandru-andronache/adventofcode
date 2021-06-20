#include "file.h"
#include "utilities.h"
#include "md5.h"
#include <iostream>

namespace aoc2016_day17 {
    int minSteps = std::numeric_limits<int>::max();
    std::string finalPath;

    void solve(int x, int y, int steps, const std::string& input, const std::string& path, std::function<bool(int, int)> comp, int maxSteps = 50) {
        if (steps >= maxSteps) {
            return;
        }
        if (x == 3 && y == 3) {
            if (comp(minSteps, steps)) {
                minSteps = steps;
                finalPath = path;
            }
            return;
        }
        std::string md5 = md5::calculateMD5(input + path);
        if (md5[0] >= 'b' && md5[0] <= 'f' && x > 0) {
            solve(x - 1, y, steps + 1, input, path + "U", comp, maxSteps);
        }
        if (md5[1] >= 'b' && md5[1] <= 'f' && x < 3) {
            solve(x + 1, y, steps + 1, input, path + "D", comp, maxSteps);
        }
        if (md5[2] >= 'b' && md5[2] <= 'f' && y > 0) {
            solve(x, y - 1, steps + 1, input, path + "L", comp, maxSteps);
        }
        if (md5[3] >= 'b' && md5[3] <= 'f' && y < 3) {
            solve(x, y + 1, steps + 1, input, path + "R", comp, maxSteps);
        }
    }

    std::string part_1(const std::string& input) {
        minSteps = std::numeric_limits<int>::max();
        solve(0, 0, 0, input, "", [](int a, int b) {
            return a > b;
        });
        return finalPath;
    }

    int part_2(const std::string& input) {
        minSteps = std::numeric_limits<int>::min();
        solve(0, 0, 0, input, "", [](int a, int b) {
            return a < b;
            }, 1000);
        return finalPath.size();
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day17::part_1("yjjvjgan") << std::endl;
    std::cout << "Part 2: " << aoc2016_day17::part_2("yjjvjgan") << std::endl;

    return 0;
}
#endif
