#include "file.h"
#include "utilities.h"
#include <map>
#include <ranges>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day07 {

    bool valid(const std::string& name, const std::map<char, std::vector<std::string>>& rules) {
        if (name.size() == 1) {
            return true;
        }
        if (!rules.contains(name.front())) {
            return false;
        }
        bool sol = false;
        for (const auto& rule : rules.at(name.front())) {
            if (name[1] == rule[0]) {
                sol = sol || valid(name.substr(1, name.size() - 1), rules);
            }
        }
        return sol;
    }

    void count(char current, const std::map<char, std::vector<std::string>>& rules, int size, int& total) {
        if (size > 11) {
            return;
        }
        if (size >= 7) {
            total++;
        }
        if (!rules.contains(current)) {
            return;
        }
        for (const auto& rule : rules.at(current)) {
            count(rule[0], rules, size + 1, total);
        }
    }

    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> names = utils::splitString(lines[0], ",");
        std::map<char, std::vector<std::string>> rules;

        for (int i = 2; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], ", >");
            rules.insert({tokens[0][0], {tokens.begin() + 1, tokens.end()}});
        }

        for (const auto& name : names) {
            if (valid(name, rules)) {
                return name;
            }
        }
        return "";
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> names = utils::splitString(lines[0], ",");
        std::map<char, std::vector<std::string>> rules;

        for (int i = 2; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], ", >");
            rules.insert({tokens[0][0], {tokens.begin() + 1, tokens.end()}});
        }

        int sum = 0;
        for (int i = 0; i < names.size(); ++i) {
            if (valid(names[i], rules)) {
                sum += i + 1;
            }
        }
        return sum;
    }

    unsigned long long part_3(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> names = utils::splitString(lines[0], ",");
        std::map<char, std::vector<std::string>> rules;

        for (int i = 2; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], ", >");
            rules.insert({tokens[0][0], {tokens.begin() + 1, tokens.end()}});
        }

        std::vector<std::string> clearNames;
        for (const auto& name : names) {
            bool valid = true;
            for (const auto& n : clearNames) {
                if (n.size() < name.size() && name.substr(0, n.size()) == n) {
                    valid = false;
                }
            }
            if (valid) {
                clearNames.push_back(name);
            }
        }

        int total = 0;
        for (const auto& name : clearNames) {
            if (!valid(name, rules)) {
                continue;
            }
            int tmp = 0;
            count(name.back(), rules, name.size(), tmp);
            total += tmp;
        }

        return total;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day07 {
    TEST(Testscodes_2025Day07, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day07/input/input_part_1_test.in"), "Oroneth");
    }

    TEST(Testscodes_2025Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day07/input/input_part_1.in"), "Kyjorath");
    }

    TEST(Testscodes_2025Day07, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day07/input/input_part_2_test.in"), 23);
    }

    TEST(Testscodes_2025Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day07/input/input_part_2.in"), 2822);
    }

    TEST(Testscodes_2025Day07, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day07/input/input_part_3_test.in"), 25);
    }

    TEST(Testscodes_2025Day07, part_3_test_2) {
        ASSERT_EQ(part_3("../codes_2025/day07/input/input_part_3_test_2.in"), 1154);
    }

    TEST(Testscodes_2025Day07, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day07/input/input_part_3.in"), 1976069);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day07::part_1("../codes_2025/day07/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day07::part_2("../codes_2025/day07/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day07::part_3("../codes_2025/day07/input/input_part_3.in"));

    return 0;
}
#endif
