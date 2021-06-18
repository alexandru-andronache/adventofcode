#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <array>

namespace aoc2015_day11 {
    std::string nextPassword(std::string password) {
        int i = password.size() - 1;
        while (password[i] == 'z') {
            i--;
        }
        password[i]++;
        for (int j = i + 1; j < password.size(); ++j) {
            password[j] = 'a';
        }
        return password;
    }

    bool isValid(std::string_view password) {
        bool valid = false;
        for (int i = 0; i < password.size() - 2; ++i) {
            if (password[i] + 1 == password[i + 1] && password[i + 1] + 1 == password[i + 2]) {
                valid = true;
            }
        }
        for (const auto& c : password) {
            valid = valid && (c != 'i' && c != 'o' && c != 'l');
        }
        std::array<int, 26> letters{0};
        for (int i = 0; i < password.size() - 1; ++i) {
            if (password[i] == password[i + 1]) {
                letters[password[i] - 'a'] = 1;
            }
        }
        valid = valid && (std::count(letters.begin(), letters.end(), 1) >= 2);
        return valid;
    }

    std::string solve(std::string password) {
        while (true) {
            std::string next = nextPassword(password);
            if (isValid(next)) {
                return next;
            }
            password = next;
        }
    }

    std::string part_1(const std::string& password) {
        return solve(password);
    }

    std::string part_2(const std::string& password) {
        std::string first_password = solve(password);
        return solve(first_password);
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day11::part_1("cqjxjnds") << std::endl;
    std::cout << "Part 2: " << aoc2015_day11::part_2("cqjxjnds") << std::endl;

    return 0;
}
#endif
