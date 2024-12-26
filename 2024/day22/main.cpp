#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day22 {
    long long get_next(long long secret) {
        secret = ((secret << 6) ^ secret) % 16777216;
        secret = ((secret >> 5) ^ secret) % 16777216;
        secret = ((secret << 11) ^ secret) % 16777216;
        return secret;
    }
    unsigned long long part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        unsigned long long sum = 0;

        for (const auto& nr : input) {
            long long secret = nr;
            for (int step = 0; step < 2000; ++step) {
                secret = get_next(secret);
            }
            sum += secret;
        }

        return sum;
    }

    int part_2(std::string_view path) {
        constexpr int MAX = 18 * 19 * 19 * 19 + 18 * 19 * 19 + 18 * 19 + 18 + 1;
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::vector<int> total(MAX, 0);
        std::vector<std::pair<int, int>> history;
        std::bitset<MAX> visited;

        for (const auto& nr : input) {
            history.clear();
            visited.reset();
            long long secret = nr;
            int prev = secret % 10;
            for (int step = 0; step < 2000; ++step) {
                secret = get_next(secret);
                history.emplace_back(secret % 10 - prev + 9, secret % 10);
                prev = secret % 10;
            }
            for (int i = 0; i < history.size() - 3; ++i) {
                long long key = (history[i].first) * std::pow(19, 3) +
                          history[i + 1].first * std::pow(19, 2) +
                          history[i + 2].first * 19 +
                          history[i + 3].first;
                if (!visited.test(key)) {
                    total[key] += history[i + 3].second;
                    visited.flip(key);
                }
            }
        }

        int max = *std::max_element(total.begin(), total.end());
        return max;
    }
}

#ifdef TESTING
namespace aoc2024_day22{
    TEST(Tests2024Day22, part_1_test) {
        ASSERT_EQ(part_1("../2024/day22/input_test.in"), 37327623);
    }

    TEST(Tests2024Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day22/input.in"), 13584398738);
    }

    TEST(Tests2024Day22, part_2_test) {
        ASSERT_EQ(part_2("../2024/day22/input_test2.in"), 23);
    }

    TEST(Tests2024Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day22/input.in"), 1612);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day22::part_1("../2024/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day22::part_2("../2024/day22/input.in") << std::endl;

    return 0;
}
#endif
