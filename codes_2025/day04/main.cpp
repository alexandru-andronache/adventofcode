#include "file.h"
#include <fmt/printf.h>
#include "utilities.h"

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day04 {
    const int part_1_turns = 2025;
    const unsigned long long part_2_turns = 10000000000000;
    const int part_3_turns = 100;
    int part_1(std::string_view path) {
        const std::vector<int> nr = file::readFileAsArrayInt(path);
        return (nr.front() * part_1_turns) / nr.back();
    }

    unsigned long long part_2(std::string_view path) {
        const std::vector<int> nr = file::readFileAsArrayInt(path);
        return (nr.back() * part_2_turns) / nr.front() + 1;
    }

    unsigned long long part_3(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long sol = stoull(lines[0]) * part_3_turns;
        for (int i = 1; i < lines.size() - 1; ++i) {
            std::vector<int> tokens = utils::splitStringToInt(lines[i], "|");
            sol *= tokens[1] / tokens[0];
        }

        return sol / stoull(lines.back());
    }
}

#ifdef TESTING
namespace aoccodes_2025_day04 {
    TEST(Testscodes_2025Day04, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day04/input/input_part_1_test.in"), 15888);
    }

    TEST(Testscodes_2025Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day04/input/input_part_1.in"), 13410);
    }

    TEST(Testscodes_2025Day04, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day04/input/input_part_2_test.in"), 1274509803922);
    }

    TEST(Testscodes_2025Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day04/input/input_part_2.in"), 2923408845739);
    }

    TEST(Testscodes_2025Day04, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day04/input/input_part_3_test.in"), 6818);
    }

    TEST(Testscodes_2025Day04, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day04/input/input_part_3.in"), 177671681932);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day04::part_1("../codes_2025/day04/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day04::part_2("../codes_2025/day04/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day04::part_3("../codes_2025/day04/input/input_part_3.in"));

    return 0;
}
#endif
