#include "file.h"
#include "utilities.h"
#include "point.h"
#include <iostream>
#include <numeric>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day14 {
    int part_1(std::string_view path, int maxX = 103, int maxY = 101) {
        constexpr int seconds = 100;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<int> quadrants{0, 0, 0, 0};
        for (const auto & line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "=, ");
            point::point position{std::stoi(tokens[2]), std::stoi(tokens[1])};
            point::point velocity{std::stoi(tokens[5]), std::stoi(tokens[4])};
            for (int second = 0; second < seconds; ++second) {
                position += velocity;
                position += point::point{maxX, maxY};
                position %= point::point{maxX, maxY};
            }
            if (position.getX() < maxX / 2 && position.getY() < maxY / 2) {
                ++quadrants[0];
            } else if (position.getX() > maxX / 2 && position.getY() < maxY / 2) {
                ++quadrants[1];
            } else if (position.getX() < maxX / 2 && position.getY() > maxY / 2) {
                ++quadrants[2];
            } else if (position.getX() > maxX / 2 && position.getY() > maxY / 2) {
                ++quadrants[3];
            }
        }
        return quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
    }

    int part_2(std::string_view path, int maxX = 103, int maxY = 101) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::pair<point::point, point::point>> points;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "=, ");
            points.push_back({{std::stoi(tokens[2]), std::stoi(tokens[1])}, {std::stoi(tokens[5]), std::stoi(tokens[4])}});
        }
        std::vector<std::string> pattern = file::readFileAsArrayString("../2024/day14/pattern.in");

        bool found = false;
        int steps = 0;
        while (!found) {
            steps++;
            std::vector<std::string> map(maxX, std::string(maxY, '.'));
            for (auto& p : points) {
                p.first += p.second;
                p.first += point::point{maxX, maxY};
                p.first %= point::point{maxX, maxY};
                map[p.first.getX()][p.first.getY()] = '#';
            }
            for (int i = 0; i < maxX && !found; ++i) {
                if (std::string::size_type pos = map[i].find(pattern[0]); pos != std::string::npos) {
                    found = true;
                    for (int j = 1; j < pattern.size() && found; ++j) {
                        if (map[i + j].substr(pos, pattern[j].size()) != pattern[j]) {
                            found = false;
                        }
                    }
                }
            }
        }

        return steps;
    }
}

#ifdef TESTING
namespace aoc2024_day14{
    TEST(Tests2024Day14, part_1_test) {
        ASSERT_EQ(part_1("../2024/day14/input_test.in", 7, 11), 12);
    }

    TEST(Tests2024Day14, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day14/input.in"), 220971520);
    }

    TEST(Tests2024Day14, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day14/input.in"), 6355);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day14::part_1("../2024/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2024_day14::part_2("../2024/day14/input.in") << std::endl;

    return 0;
}
#endif
