#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day21 {
    std::map<std::string_view, std::vector<std::string>> bigKeypad{{"A0", {"<"}},
    {"A1", {"^<<"}}, {"A2", {"^<", "<^"}}, {"A3", {"^"}}, {"A4", {"^^<<"}},
    {"A5", {"^^<", "<^^"}}, {"A6", {"^^"}}, {"A7", {"^^^<<"}},
    {"A8", {"^^^<", "<^^^"}},
    {"A9", {"^^^"}},
    {"0A", {">"}}, {"01", {"^<"}}, {"02", {"^"}},
    {"03", {"^>", ">^"}}, {"04", {"^^<"}}, {"05", {"^^"}},
    {"06", {"^^>", ">^^"}}, {"07", {"^^^<"}}, {"08", {"^^^"}},
    {"09", {"^^^>", ">^^^"}}, {"1A", {">>v"}}, {"10", {">v"}},
    {"12", {">"}}, {"13", {">>"}}, {"14", {"^"}}, {"15", {"^>", ">^"}},
    {"16", {">>^", "^>>"}}, {"17", {"^^"}}, {"18", {"^^>", ">^^"}},
    {"19", {">>^^", "^^>>"}},
    {"2A", {">v", "v>"}}, {"20", {"v"}}, {"21", {"<"}}, {"23", {">"}},
    {"24", {"^<", "<^"}}, {"25", {"^"}}, {"26", {"^>", ">^"}},
    {"27", {"^^<", "<^^"}},{"28", {"^^"}}, {"29", {"^^>", ">^^"}},
    {"3A", {"v"}}, {"30", {"v<", "<v"}},
    {"31", {"<<"}}, {"32", {"<"}}, {"34", {"<<^", "^<<"}},
    {"35", {"^<", "<^"}}, {"36", {"^"}},
    {"37", {"<<^^", "^^<<"}}, {"38", {"^^<", "<^^"}}, {"39", {"^^"}},
    {"4A", {">>vv"}},
    {"40", {">vv"}}, {"41", {"v"}}, {"42", {"v>", ">v"}},
    {"43", {"v>>", ">>v"}}, {"45", {">"}},
    {"46", {">>"}}, {"47", {"^"}}, {"48", {"^>", ">^"}},
    {"49", {"^>>",  ">>^"}},
    {"5A", {">vv", "vv>"}}, {"50", {"vv"}}, {"51", {"v<", "<v"}},
    {"52", {"v"}},
    {"53", {"v>", ">v"}}, {"54", {"<"}}, {"56", {">"}},
    {"57", {"^<", "<^"}}, {"58", {"^"}},
    {"59", {"^>", ">^"}},
    {"6A", {"vv"}}, {"60", {"vv<", "<vv"}}, {"61", {"<<v", "v<<"}},
    {"62", {"v<", "<v"}}, {"63", {"v"}},
    {"64", {"<<"}}, {"65", {"<"}}, {"67", {"^<<", "<<^"}},
    {"68", {"^<", "<^"}}, {"69", {"^"}},
    {"7A", {">>vvv"}}, {"70", {">vvv"}},
    {"71", {"vv"}}, {"72", {"vv>", ">vv"}}, {"73", {"vv>>", ">>vv"}},
    {"74", {"v"}}, {"75", {">v", "v>"}},
    {"76", {">>v", "v>>"}}, {"78", {">"}}, {"79", {">>"}},
    {"8A", {"vvv>", ">vvv"}},
    {"80", {"vvv"}}, {"81", {"vv<", "<vv"}}, {"82", {"vv"}},
    {"83", {"vv>", ">vv"}}, {"84", {"v<", "<v"}}, {"85", {"v"}},
    {"86", {"v>", ">v"}}, {"87", {"<"}}, {"89", {">"}},
    {"9A", {"vvv"}}, {"90", {"vvv<", "<vvv"}},
    {"91", {"<<vv", "vv<<"}}, {"92", {"vv<", "<vv"}}, {"93", {"vv"}},
    {"94", {"<<v", "v<<"}}, {"95", {"<v", "v<"}}, {"96", {"v"}},
    {"97", {"<<"}}, {"98", {"<"}}};

    std::map<std::string_view, std::string> smallKeypad{{"A^", "<A"},
    {"A<", "v<<A"}, {"Av", "<vA"}, {"A>", "vA"},
    {"^A", ">A"}, {"^<", "v<A"}, {"^v", "vA"}, {"^>", "v>A"},
    {"<A", ">>^A"}, {"<^", ">^A"}, {"<v", ">A"}, {"<>", ">>A"},
    {"vA", "^>A"}, {"v^", "^A"}, {"v<", "<A"}, {"v>", ">A"},
    {">A", "^A"}, {">^", "<^A"}, {"><", "<<A"}, {">v", "<A"}};

    std::map<std::pair<std::string, int>, unsigned long long> cache;

    std::vector<std::string> processBigKeypad(const std::vector<std::string>& lines) {
        std::vector<std::string> final;
        for (auto line : lines) {
            line = "A" + line;
            std::vector<std::string> result;
            result.emplace_back("");
            for (int i = 0; i < line.size() - 1; ++i) {
                std::vector<std::string> paths;
                if (line[i] == line[i + 1]) {
                    paths.emplace_back("");
                }
                else {
                    paths = bigKeypad.at(line.substr(i, 2));
                }
                std::vector<std::string> newResult;
                for (const auto& path : paths) {
                    for (const auto& r : result) {
                        newResult.push_back(r + path + "A");
                    }
                }
                result = newResult;
            }
            final.insert(final.end(), result.begin(), result.end());
        }
        return final;
    }

    unsigned long long process(const std::string& str, int level, int maxLevel) {
        unsigned long long sol = 0;
        std::vector<std::string> splits;
        std::string current;
        for (const auto& c : str) {
            current += c;
            if (c == 'A') {
                splits.push_back(current);
                current = "";
            }
        }

        for (auto split : splits) {
            std::string result;
            split = "A" + split;
            if (cache.contains({split, level})) {
                sol += cache.at({split, level});
                continue;
            }
            for (int i = 0; i < split.size() - 1; ++i) {
                if (split[i] != split[i + 1]) {
                    result += smallKeypad.at(split.substr(i, 2));
                }
                else {
                    result += "A";
                }
            }

            unsigned long long k;
            if (level < maxLevel) {
                k = process(result, level + 1, maxLevel);
            }
            else {
                k = result.size();
            }
            cache.insert({{split, level}, k});
            sol += k;
        }

        return sol;
    }

    unsigned long long solve(std::string_view path, int level) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        cache.clear();
        for (const auto& line : lines) {
            std::vector<std::string> result = processBigKeypad({line});
            unsigned long long min = std::numeric_limits<unsigned long long>::max();
            for (const auto& r: result) {
                unsigned long long l = process(r, 1, level);
                min = std::min(min, l);
            }

            int nr = 0;
            for (const auto& c : line) {
                if (c >= '0' &&  c <= '9') {
                    nr = nr * 10 + c - '0';
                }
            }
            sol += min * nr;
        }

        return sol;
    }

    unsigned long long part_1(std::string_view path) {
        return solve(path, 2);
    }

    unsigned long long part_2(std::string_view path) {
        return solve(path, 25);
    }
}

#ifdef TESTING
namespace aoc2024_day21 {
    TEST(Tests2024Day21, part_1_test) {
        ASSERT_EQ(part_1("../2024/day21/input_test.in"), 126384);
    }

    TEST(Tests2024Day21, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day21/input.in"), 270084);
    }

    TEST(Tests2024Day21, part_2_test) {
        ASSERT_EQ(part_2("../2024/day21/input_test.in"), 154115708116294);
    }

    TEST(Tests2024Day21, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day21/input.in"), 329431019997766);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day21::part_1("../2024/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day21::part_2("../2024/day21/input.in") << std::endl;

    return 0;
}
#endif
