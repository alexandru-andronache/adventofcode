#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>

namespace aoc2016_day20 {
    long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<long long, long long>> pairs;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, "-");
            pairs.emplace_back(std::stoll(s[0]), std::stoll(s[1]));
        }

        std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second < b.second;
        });

        int index = 1;
        long long end = pairs[0].second;
        while (true) {
            if (pairs[index].first > end + 1) {
                return end + 1;
            }
            else {
                end = pairs[index].second;
                index++;
            }
        }


        return 0;
    }

    long long part_2(std::string_view path, long long start = 0, long long finish = 4294967295) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<long long, long long>> pairs;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, "-");
            pairs.emplace_back(std::stoll(s[0]), std::stoll(s[1]));
        }

        std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second < b.second;
        });

        long long sol = pairs[0].first - start;
        long long end = pairs[0].second;
        for (int i = 1; i < pairs.size(); ++i) {
            if (pairs[i].first > end + 1) {
                sol += pairs[i].first - end - 1;
            }
            end = std::max(pairs[i].second, end);
        }
        sol += finish - end;

        return sol;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day20::part_1("../2016/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day20::part_2("../2016/day20/input.in") << std::endl;

    return 0;
}
#endif
