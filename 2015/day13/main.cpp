#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <limits>
#include <algorithm>

namespace aoc2015_day13 {
    int solve(const std::vector<std::string>& input, int nrPeople) {
        std::map<std::string, int> people;
        std::vector<std::vector<int>> happiness(nrPeople, std::vector(nrPeople, 0));
        int maxHappiness = std::numeric_limits<int>::min();

        int k = 0;
        for (const auto& line : input) {
            std::vector<std::string> words = utils::splitString(line,  " .");
            if (people.find(words[0]) == people.end()) {
                people.insert({words[0], k++});
            }
            if (people.find(words[10]) == people.end()) {
                people.insert({words[10], k++});
            }
            if (words[2] == "gain") {
                happiness[people[words[0]]][people[words[10]]] = std::stoi(words[3]);
            }
            else {
                happiness[people[words[0]]][people[words[10]]] = -std::stoi(words[3]);
            }
        }

        std::vector<int> perm(nrPeople);
        std::iota(perm.begin(), perm.end(), 0);
        do {
            int sum = happiness[perm.back()][perm[0]] + happiness[perm[0]][perm.back()];
            for (int i = 0; i < perm.size() - 1; ++i) {
                sum += happiness[perm[i]][perm[i + 1]] + happiness[perm[i + 1]][perm[i]];
            }
            maxHappiness = std::max(maxHappiness, sum);
        } while(std::next_permutation(perm.begin(), perm.end()));

        return maxHappiness;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int nrPeople = 0;
        while ((nrPeople - 1) * nrPeople < input.size()) {
            nrPeople++;
        }
        return solve(input, nrPeople);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int nrPeople = 1;
        while ((nrPeople - 1) * nrPeople < input.size()) {
            nrPeople++;
        }
        return solve(input, nrPeople + 1);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day13::part_1("../2015/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day13::part_2("../2015/day13/input.in") << std::endl;

    return 0;
}
#endif
