#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2015_day14 {
    int travelDistance(int speed, int duration, int restTime, int totalTime) {
        int time = 0;
        int distance = 0;
        while (time < totalTime) {
            distance += speed * std::min(duration, totalTime - time);
            time += std::min(duration, totalTime - time);
            time += restTime;
        }
        return distance;
    }

    int part_1(std::string_view path, int totalTime) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        int maxDistance = std::numeric_limits<int>::min();
        for (const auto& line : input) {
            std::vector<std::string> words = utils::splitString(line, " ");
            maxDistance = std::max(maxDistance, travelDistance(std::stoi(words[3]),
                                                               std::stoi(words[6]),
                                                               std::stoi(words[13]),
                                                               totalTime));
        }
        return maxDistance;
    }

    int part_2(std::string_view path, int totalTime) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        struct reindeer{
            reindeer(int s, int fly, int rest) {
                points = 0;
                speed = s;
                flyTime = fly;
                restTime = rest;
                isFlying = true;
                currentTime = fly;
                distance = 0;
            }
            int points;
            int speed;
            int flyTime;
            int restTime;
            bool isFlying;
            int currentTime;
            int distance;
        };
        std::vector<reindeer> reindeers;
        for (const auto& line : input) {
            std::vector<std::string> words = utils::splitString(line, " ");
            reindeers.emplace_back(std::stoi(words[3]),
                                   std::stoi(words[6]),
                                   std::stoi(words[13]));
        }

        for (int time = 0; time < totalTime; ++time) {
            for (auto& r : reindeers) {
                r.currentTime--;
                r.distance += r.speed * r.isFlying;
                if (r.currentTime == 0) {
                    r.isFlying = !r.isFlying;
                    r.currentTime = r.isFlying ? r.flyTime : r.restTime;
                }
            }
            auto max = std::max_element(reindeers.begin(), reindeers.end(), [](const auto& a, const auto&b) {
                return a.distance < b.distance;
            });
            for (auto& r : reindeers) {
                if (r.distance == max->distance) {
                    r.points++;
                }
            }
        }

        auto max = std::max_element(reindeers.begin(), reindeers.end(), [](const auto& a, const auto&b) {
            return a.points < b.points;
        });
        return max->points;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day14::part_1("../2015/day14/input.in", 2503) << std::endl;
    std::cout << "Part 1: " << aoc2015_day14::part_2("../2015/day14/input.in", 2503) << std::endl;

    return 0;
}
#endif
