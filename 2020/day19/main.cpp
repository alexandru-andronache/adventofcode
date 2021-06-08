#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2020_day19 {
    const int N = 1000;

    std::pair<bool, int> match(const std::vector<std::vector<std::vector<int>>> &sequence,
                               int rule,
                               std::string_view message) {
        for (const auto &branch : sequence[rule]) {
            bool matching = true;
            int position = 0;
            for (const auto &nr : branch) {
                if (nr > N) {
                    matching = matching && (message[position] - 'a' == nr - N - 'a');
                    position++;
                } else {
                    auto result = match(sequence, nr, message.substr(position));
                    matching = matching && result.first;
                    position += result.second;
                }
            }
            if (matching) {
                return {true, position};
            }
        }
        return {false, 0};
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<std::vector<int>>> sequence(200);
        int index = 0;
        while (!input[index].empty()) {
            std::vector<std::string> w = utils::splitString(input[index], ": \"");
            sequence[std::stoi(w[0])].push_back(std::vector<int>());
            for (int i = 1; i < w.size(); ++i) {
                if (w[i] == "|") {
                    sequence[std::stoi(w[0])].push_back(std::vector<int>());
                } else {
                    if (w[i] == "a" || w[i] == "b") {
                        sequence[std::stoi(w[0])].back().push_back(N + w[i][0]);
                    } else {
                        sequence[std::stoi(w[0])].back().push_back(std::stoi(w[i]));
                    }
                }
            }
            index++;
        }
        index++;

        int sol = 0;
        while (index < input.size()) {
            auto result = match(sequence, 0, input[index]);
            if (result.first && result.second == input[index].size()) {
                sol++;
            }
            index++;
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::vector<std::vector<int>>> sequence(200);
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int index = 0;
        while (!input[index].empty()) {
            std::vector<std::string> w = utils::splitString(input[index], ": \"");
            sequence[std::stoi(w[0])].push_back(std::vector<int>());
            for (int i = 1; i < w.size(); ++i) {
                if (w[i] == "|") {
                    sequence[std::stoi(w[0])].push_back(std::vector<int>());
                } else {
                    if (w[i] == "a" || w[i] == "b") {
                        sequence[std::stoi(w[0])].back().push_back(N + w[i][0]);
                    } else {
                        sequence[std::stoi(w[0])].back().push_back(std::stoi(w[i]));
                    }
                }
            }
            index++;
        }

        index++;

        int sol = 0;
        while (index < input.size()) {
            int position = 0;
            int occurrencesOf42 = 0;
            for (auto result = match(sequence, 42, input[index]); result.first; occurrencesOf42++) {
                position += result.second;
                result = match(sequence, 42, input[index].substr(position));
            }
            int occurrencesOf31 = 0;
            for (auto result = match(sequence, 31, input[index].substr(position)); result.first; occurrencesOf31++) {
                position += result.second;
                result = match(sequence, 31, input[index].substr(position));
            }
            if (occurrencesOf42 > 1 && occurrencesOf42 - 1 >= occurrencesOf31 && occurrencesOf31 > 0 &&
                position == input[index].size()) {
                sol++;
            }
            index++;
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day19::part_1("../2020/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day19::part_2("../2020/day19/input.in") << std::endl;

    return 0;
}
#endif
