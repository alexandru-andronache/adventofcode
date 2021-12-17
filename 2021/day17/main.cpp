#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day17 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<std::string> tokens = utils::splitString(input, " : =.,");
        int xStart = std::stoi(tokens[3].c_str());
        int xEnd = std::stoi(tokens[4].c_str());
        int yStart = std::stoi(tokens[6].c_str());
        int yEnd = std::stoi(tokens[7].c_str());
        int sol = std::numeric_limits<int>::min();

        for (int x = -1000; x <= 1000; ++x) {
            for (int y = -1000; y <= 1000; ++y) {
                int posX = 0, posY = 0;
                int speedX = x, speedY = y;
                int maxY = std::numeric_limits<int>::min();
                bool wasSolution = false;
                while (posY >= yStart && !wasSolution) {
                    posX += speedX;
                    posY += speedY;
                    maxY = std::max(maxY, posY);
                    if (speedX < 0) {
                        speedX++;
                    }
                    else if (speedX != 0) {
                        speedX--;
                    }
                    speedY--;
                    if (posX >= xStart && posX <= xEnd && posY >= yStart && posY <= yEnd) {
                        wasSolution = true;
                        sol = std::max(sol, maxY);
                    }
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<std::string> tokens = utils::splitString(input, " : =.,");
        int xStart = std::stoi(tokens[3].c_str());
        int xEnd = std::stoi(tokens[4].c_str());
        int yStart = std::stoi(tokens[6].c_str());
        int yEnd = std::stoi(tokens[7].c_str());
        int sol = 0;

        for (int x = -1000; x <= 1000; ++x) {
            for (int y = -1000; y <= 1000; ++y) {
                int posX = 0, posY = 0;
                int speedX = x, speedY = y;
                bool wasSolution = false;
                while (posY >= yStart && !wasSolution) {
                    posX += speedX;
                    posY += speedY;
                    if (speedX < 0) {
                        speedX++;
                    }
                    else if (speedX != 0) {
                        speedX--;
                    }
                    speedY--;
                    if (posX >= xStart && posX <= xEnd && posY >= yStart && posY <= yEnd) {
                        std::cout << x << "," << y << std::endl;
                        sol++;
                        wasSolution = true;
                    }
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day17::part_1("../2021/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day17::part_2("../2021/day17/input.in") << std::endl;

    return 0;
}
#endif
