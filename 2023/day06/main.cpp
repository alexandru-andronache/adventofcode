#include "file.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <vector>

namespace aoc2023_day06 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 1;
        std::vector<std::string> t1 = utils::splitString(input[0], " ");
        std::vector<std::string> t2 = utils::splitString(input[1], " ");
        std::vector<int> time;
        std::vector<int> dist;
        for (int i = 1; i < t1.size(); ++i) {
            time.push_back(std::stoi(t1[i]));
            dist.push_back(std::stoi(t2[i]));
        }

        for (int i = 0; i < time.size(); ++i) {
            int s = 0;
            for (int j = 0; j <= time[i]; ++j) {
                int speed = j;
                int distance = (time[i] - j) * speed;
                if (distance > dist[i]) {
                    s++;
                }
            }
            sol = sol * s;
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        std::vector<std::string> t1 = utils::splitString(input[0], " ");
        std::vector<std::string> t2 = utils::splitString(input[1], " ");
        std::string t;
        std::string d;
        for (int i = 1; i < t1.size(); ++i) {
            t += t1[i];
            d += t2[i];
        }
        int time = std::stoi(t);
        unsigned long long dist = std::stoull(d);


        for (unsigned long long j = 0; j <= time; ++j) {
            unsigned long long speed = j;
            unsigned long long distance = (time - j) * speed;
            if (distance > dist) {
                sol++;
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day06::part_1("../2023/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day06::part_2("../2023/day06/input.in") << std::endl;

    return 0;
}
#endif
