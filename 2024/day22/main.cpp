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

    int advance(long long& secret, int& prev) {
        int old = prev;
        secret = get_next(secret);
        prev = secret % 10;
        return secret % 10 - old + 9;
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
        int a, b, c, d;

        for (const auto& nr : input) {
            std::bitset<MAX> visited;
            long long secret = nr;
            int prev = secret % 10;
            a = advance(secret, prev);
            b = advance(secret, prev);
            c = advance(secret, prev);
            for (int step = 3; step < 2000; ++step) {
                d = advance(secret, prev);
                int key = a * 19 * 19 * 19 + b * 19 * 19 + c * 19 + d;
                if (!visited.test(key)) {
                    total[key] += secret % 10;
                    visited.flip(key);
                }
                a = b;
                b = c;
                c = d;
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
