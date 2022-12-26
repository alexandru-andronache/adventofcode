#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>
#include <deque>

namespace aoc2022_day20 {
    int64_t dataAt(const int64_t pos, const std::vector<long long>& data, const std::vector<int>& position) {
        for (int i = 0; i < position.size(); ++i) {
            if (position[i] == pos % (int64_t)position.size())
                return data[i];
        }
        return 0;
    }

    void advance(const std::vector<long long>& data, std::vector<int>& position) {
        const auto modulus = (int64_t)data.size();
        for (int i = 0; i < modulus; ++i) {
            if (data[i] % (modulus - 1) == 0)
                continue;
            const auto oldPos = position[i];
            const auto newRawPos = oldPos + data[i] % (modulus - 1);
            const auto newPos = [&]() {
                if (0 < newRawPos and newRawPos < modulus)
                    return newRawPos;
                if (newRawPos <= 0)
                    return newRawPos + modulus - 1;
                return newRawPos - modulus + 1;
            }();
            for (auto &ele : position) {
                if (oldPos < newPos and oldPos <= ele and ele <= newPos) {
                    ele = (ele - 1 + modulus) % modulus;
                } else if (newPos < oldPos and newPos <= ele and ele <= oldPos) {
                    ele = (ele + 1) % modulus;
                }
            }
            position[i] = newPos;
        }
    }

    long long part_1(std::string_view path) {
        std::vector<long long> nr = file::readFileAsArrayLongLong(path, "\n");
        std::vector<int> pos;
        int posOfZero = 0;
        for (int i = 0; i < nr.size(); ++i) {
            if (nr[i] == 0) {
                posOfZero = i;
            }
            pos.push_back(i);
        }

        advance(nr, pos);

        return dataAt(1000 + pos[posOfZero], nr, pos) + dataAt(2000 + pos[posOfZero], nr, pos) + dataAt(3000 + pos[posOfZero], nr, pos);
    }

    long long part_2(std::string_view path) {
        const int KEY = 811589153;
        std::vector<long long> nr = file::readFileAsArrayLongLong(path, "\n");
        std::vector<int> pos;
        int posOfZero = 0;
        for (int i = 0; i < nr.size(); ++i) {
            nr[i] = nr[i] * KEY;
            if (nr[i] == 0) {
                posOfZero = i;
            }
            pos.push_back(i);
        }

        for (int i = 0; i < 10; ++i) {
            advance(nr, pos);
        }

        return dataAt(1000 + pos[posOfZero], nr, pos) + dataAt(2000 + pos[posOfZero], nr, pos) + dataAt(3000 + pos[posOfZero], nr, pos);
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day20::part_1("../2022/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day20::part_2("../2022/day20/input.in") << std::endl;

    return 0;
}
#endif