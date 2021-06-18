#include "file.h"
#include "utilities.h"
#include "verticalhexgrid.h"
#include <iostream>
#include <numeric>

namespace aoc2015_day24 {
    long long minimumQE = std::numeric_limits<int>::max();
    int minimumTerms = std::numeric_limits<int>::max();

    void solve(const std::vector<int>& input, int desiredSum, int partialSum, int index, long long qe, int terms) {
        for (int i = index; i < input.size(); ++i) {
            if (partialSum + input[i] == desiredSum) {
                if (terms + 1 == minimumTerms) {
                    minimumQE = std::min(minimumQE, qe * input[i]);
                }
                else if (terms < minimumTerms) {
                    minimumTerms = terms + 1;
                    minimumQE = qe * input[i];
                }
            } else if (partialSum + input[i] < desiredSum) {
                solve(input, desiredSum, partialSum + input[i], i + 1, qe * input[i], terms + 1);
            }
        }
    }

    long long part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        minimumQE = std::numeric_limits<int>::max();
        minimumTerms = std::numeric_limits<int>::max();
        int sum = std::accumulate(input.begin(), input.end(), 0) / 3;
        std::sort(input.begin(), input.end(), [](const auto& x, const auto& y) {
            return x > y;
        });
        solve(input, sum, 0, 0, 1, 0);
        return minimumQE;
    }

    long long part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        minimumQE = std::numeric_limits<int>::max();
        minimumTerms = std::numeric_limits<int>::max();
        int sum = std::accumulate(input.begin(), input.end(), 0) / 4;
        std::sort(input.begin(), input.end(), [](const auto& x, const auto& y) {
            return x > y;
        });
        solve(input, sum, 0, 0, 1, 0);
        return minimumQE;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day24::part_1("../2015/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day24::part_2("../2015/day24/input.in") << std::endl;

    return 0;
}
#endif
