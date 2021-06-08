#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <regex>

namespace aoc2020_day04 {
    bool validate(const std::map<std::string, bool> &data) {
        bool isValid = true;
        for (const auto &d : data) {
            if (d.first != "cid" && !d.second) {
                isValid = false;
            }
        }
        return isValid;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, bool> data{{"byr", false},
                                         {"iyr", false},
                                         {"eyr", false},
                                         {"hgt", false},
                                         {"hcl", false},
                                         {"ecl", false},
                                         {"pid", false},
                                         {"cid", false}};
        int sol = 0;
        for (const auto &line: input) {
            if (line.empty()) {
                if (validate(data)) {
                    sol++;
                }
                for (auto &d : data) {
                    d.second = false;
                }
            } else {
                std::vector<std::string> tokens = utils::splitString(line, " :");
                for (const auto &token : tokens) {
                    if (data.find(token) != data.end()) {
                        data[token] = true;
                    }
                }
            }
        }
        if (validate(data)) {
            sol++;
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, bool> data{{"byr", false},
                                         {"iyr", false},
                                         {"eyr", false},
                                         {"hgt", false},
                                         {"hcl", false},
                                         {"ecl", false},
                                         {"pid", false},
                                         {"cid", false}};
        int sol = 0;
        for (const auto &line: input) {
            if (line.empty()) {
                if (validate(data)) {
                    sol++;
                }
                for (auto &d : data) {
                    d.second = false;
                }
            } else {
                std::vector<std::string> tokens = utils::splitString(line, " :");
                for (int i = 0; i < tokens.size(); ++i) {
                    if (tokens[i] == "byr") {
                        i++;
                        data["byr"] = utils::isInteger(tokens[i]) && std::stoi(tokens[i]) >= 1920 &&
                                      std::stoi(tokens[i]) <= 2002;
                    } else if (tokens[i] == "iyr") {
                        i++;
                        data["iyr"] = utils::isInteger(tokens[i]) && std::stoi(tokens[i]) >= 2010 &&
                                      std::stoi(tokens[i]) <= 2020;
                    } else if (tokens[i] == "eyr") {
                        i++;
                        data["eyr"] = utils::isInteger(tokens[i]) && std::stoi(tokens[i]) >= 2020 &&
                                      std::stoi(tokens[i]) <= 2030;
                    } else if (tokens[i] == "hcl") {
                        i++;
                        data["hcl"] = tokens[i][0] == '#' && tokens[i].size() == 7 &&
                                      std::regex_match(tokens[i].substr(1, tokens[i].length() - 1),
                                                       std::regex("[0-9a-f]{6}"));
                    } else if (tokens[i] == "ecl") {
                        i++;
                        data["ecl"] = std::regex_match(tokens[i], std::regex("amb|blu|brn|gry|grn|hzl|oth"));
                    } else if (tokens[i] == "pid") {
                        i++;
                        data["pid"] = utils::isInteger(tokens[i]) && tokens[i].size() == 9;
                    } else if (tokens[i] == "hgt") {
                        i++;
                        int pos_cm = tokens[i].find("cm");
                        int pos_in = tokens[i].find("in");
                        data["hgt"] = (pos_cm != std::string::npos && std::stoi(tokens[i].substr(0, 3)) >= 150 &&
                                       std::stoi(tokens[i].substr(0, 3)) <= 193)
                                      || (pos_in != std::string::npos && std::stoi(tokens[i].substr(0, 2)) >= 59 &&
                                          std::stoi(tokens[i].substr(0, 2)) <= 76);
                    }
                }
            }
        }
        if (validate(data)) {
            sol++;
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day04::part_1("../2020/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day04::part_2("../2020/day04/input.in") << std::endl;

    return 0;
}
#endif
