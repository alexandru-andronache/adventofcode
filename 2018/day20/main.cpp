#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>
#include <stack>
#include <map>

namespace aoc2018_day20 {
    std::stack<std::pair<int, int>> finalPath;

    void findPath(const std::vector<std::vector<int>>& map,
                  const std::map<char, std::pair<int, std::pair<int, int>>>& directions,
                  std::vector<std::vector<int>>& pathMap,
                  unsigned long& max,
                  int N_MAX = 3000) {
        auto current = finalPath.top();
        for (const auto& dir : {'E', 'W', 'S', 'N'}) {
            if (pathMap[current.first + directions.at(dir).second.first][current.second + directions.at(dir).second.second] == 0 &&
            map[current.first][current.second] & directions.at(dir).first) {
                finalPath.push({current.first + directions.at(dir).second.first,
                           current.second + directions.at(dir).second.second});
                pathMap[current.first + directions.at(dir).second.first][current.second +
                directions.at(dir).second.second] = 1;
                findPath(map, directions, pathMap, max, N_MAX);
            }
        }
        max = std::max(max, finalPath.size());
        pathMap[current.first][current.second] = 0;
        finalPath.pop();
    }

    void findPathForAllDoors(const std::vector<std::vector<int>>& map,
                             const std::map<char, std::pair<int, std::pair<int, int>>>& directions,
                             std::vector<std::vector<int>>& pathMap,
                             unsigned long& result,
                             int N_MAX = 3000) {
        auto current = finalPath.top();
        for (const auto& dir : {'E', 'W', 'S', 'N'}) {
            if (pathMap[current.first + directions.at(dir).second.first][current.second + directions.at(dir).second.second] == 0 &&
            map[current.first][current.second] & directions.at(dir).first) {
                finalPath.push({current.first + directions.at(dir).second.first,
                           current.second + directions.at(dir).second.second});
                pathMap[current.first + directions.at(dir).second.first][current.second +
                directions.at(dir).second.second] = 1;
                if (finalPath.size() - 1 >= 1000) {
                    result++;
                }
                findPathForAllDoors(map, directions, pathMap, result, N_MAX);
            }
        }
        pathMap[current.first][current.second] = 0;
        finalPath.pop();
    }

    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        int N_MAX = 3000;
        std::vector<std::vector<int>> map;
        std::vector<std::vector<int>> pathMap;
        std::map<char, std::pair<int, std::pair<int, int>>> directions;
        unsigned long max = 0;
        directions.insert({'W', {0x01, {0, -1}}});
        directions.insert({'E', {0x02, {0, 1}}});
        directions.insert({'N', {0x04, {-1, 0}}});
        directions.insert({'S', {0x08, {1, 0}}});
        for (int i = 0; i < N_MAX; ++i) {
            map.emplace_back(N_MAX, 0);
            pathMap.emplace_back(N_MAX, 0);
        }
        int i = 1;
        std::stack<std::vector<std::pair<int, int>>> startingPoints;
        std::stack<std::vector<std::vector<std::pair<int, int>>>> endingPoints;
        startingPoints.push({{N_MAX / 2, N_MAX / 2}});
        endingPoints.push({{{N_MAX / 2, N_MAX / 2}}});
        while (input[i] != '$') {
            if (input[i] == 'W' || input[i] == 'E' || input[i] == 'S' || input[i] == 'N') {
                for (auto& point : endingPoints.top().back()) {
                    map[point.first][point.second] |= directions[input[i]].first;
                    point.first += directions[input[i]].second.first;
                    point.second += directions[input[i]].second.second;
                }
            }
            else if (input[i] == '(') {
                startingPoints.push(endingPoints.top().back());
                endingPoints.push({});
                endingPoints.top().push_back({});
                endingPoints.top().back() = startingPoints.top();
            }
            else if (input[i] == '|') {
                endingPoints.top().push_back({});
                endingPoints.top().back() = startingPoints.top();
            }
            else if (input[i] == ')') {
                std::vector<std::vector<std::pair<int, int>>> top = endingPoints.top();
                endingPoints.pop();
                endingPoints.top().pop_back();
                endingPoints.top().insert(endingPoints.top().end(), top.begin(), top.end());
                startingPoints.pop();
            }
            i++;
        }

        finalPath.push({N_MAX / 2, N_MAX / 2});
        pathMap[N_MAX / 2][N_MAX / 2] = 1;
        findPath(map, directions, pathMap, max, N_MAX);
        finalPath = std::stack<std::pair<int, int>>();

        return max - 1;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        int N_MAX = 3000;
        std::vector<std::vector<int>> map;
        std::vector<std::vector<int>> pathMap;
        std::map<char, std::pair<int, std::pair<int, int>>> directions;
        unsigned long result = 0;
        directions.insert({'W', {0x01, {0, -1}}});
        directions.insert({'E', {0x02, {0, 1}}});
        directions.insert({'N', {0x04, {-1, 0}}});
        directions.insert({'S', {0x08, {1, 0}}});
        for (int i = 0; i < N_MAX; ++i) {
            map.emplace_back(N_MAX, 0);
            pathMap.emplace_back(N_MAX, 0);
        }
        int i = 1;
        std::stack<std::vector<std::pair<int, int>>> startingPoints;
        std::stack<std::vector<std::vector<std::pair<int, int>>>> endingPoints;
        startingPoints.push({{N_MAX / 2, N_MAX / 2}});
        endingPoints.push({{{N_MAX / 2, N_MAX / 2}}});
        while (input[i] != '$') {
            if (input[i] == 'W' || input[i] == 'E' || input[i] == 'S' || input[i] == 'N') {
                for (auto& point : endingPoints.top().back()) {
                    map[point.first][point.second] |= directions[input[i]].first;
                    point.first += directions[input[i]].second.first;
                    point.second += directions[input[i]].second.second;
                }
            }
            else if (input[i] == '(') {
                startingPoints.push(endingPoints.top().back());
                endingPoints.push({});
                endingPoints.top().push_back({});
                endingPoints.top().back() = startingPoints.top();
            }
            else if (input[i] == '|') {
                endingPoints.top().push_back({});
                endingPoints.top().back() = startingPoints.top();
            }
            else if (input[i] == ')') {
                std::vector<std::vector<std::pair<int, int>>> top = endingPoints.top();
                endingPoints.pop();
                endingPoints.top().pop_back();
                endingPoints.top().insert(endingPoints.top().end(), top.begin(), top.end());
                startingPoints.pop();
            }
            i++;
        }

        finalPath.push({N_MAX / 2, N_MAX / 2});
        pathMap[N_MAX / 2][N_MAX / 2] = 1;
        findPathForAllDoors(map, directions, pathMap, result, N_MAX);

        return result;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day20::part_1("../2018/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day20::part_2("../2018/day20/input.in") << std::endl;

    return 0;
}
#endif
