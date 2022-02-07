#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <functional>
#include <limits>

namespace aoc2015_day09 {
    unsigned long long solve(const std::vector<std::string>& input, const std::function<int( int, int )> &compare, int defaultValue, int SIZE = 8) {
        std::vector<std::vector<int>> distances(SIZE, std::vector<int>(SIZE, 0));
        std::map<std::string, int> cities;
        int distance = defaultValue;
        int nr = 0;
        for (const auto& line : input) {
            std::vector<std::string> words = utils::splitString(line, " ");
            if (cities.find(words[0]) == cities.end()) {
                cities.insert({words[0], nr++});
            }
            if (cities.find(words[2]) == cities.end()) {
                cities.insert({words[2], nr++});
            }
            distances[cities[words[0]]][cities[words[2]]] = std::stoi(words[4]);
            distances[cities[words[2]]][cities[words[0]]] = std::stoi(words[4]);
        }

        std::vector<int> perm(SIZE);
        std::iota(perm.begin(), perm.end(), 0);
        do {
            int dist = 0;
            for (int i = 0; i < perm.size() - 1; ++i) {
                dist += distances[perm[i]][perm[i + 1]];
            }
            distance = compare(distance, dist);
        } while(std::next_permutation(perm.begin(), perm.end()));

        return distance;
    }

    unsigned long long part_1(std::string_view path, int SIZE = 8) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, [](int a, int b) {return std::min(a, b);}, std::numeric_limits<int>::max(), SIZE);
    }

    unsigned long long part_2(std::string_view path, int SIZE = 8) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        return solve(input, [](int a, int b) {return std::max(a, b);}, std::numeric_limits<int>::min(), SIZE);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day09::part_1("../2015/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day09::part_2("../2015/day09/input.in") << std::endl;

    return 0;
}
#endif
