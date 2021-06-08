#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>

namespace aoc2020_day20 {

    struct Tile {
        int id{};
        std::vector<std::vector<bool>> rows;
        bool found = false;
    };

    const std::vector<std::vector<bool>> seaMonster{{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true,  false},
                                                    {true,  false, false, false, false, true,  true,  false, false, false, false, true,  true,  false, false, false, false, true,  true,  true},
                                                    {false, true,  false, false, true,  false, false, true,  false, false, true,  false, false, true,  false, false, true,  false, false, false}};

    std::pair<int, int> calculateNorth(const std::vector<std::vector<bool>> &rows) {
        std::vector<bool> reverse(rows.front().size());
        std::reverse_copy(rows.front().begin(), rows.front().end(), reverse.begin());
        return {utils::decimalToInt(rows.front()), utils::decimalToInt(reverse)};
    }

    std::pair<int, int> calculateSouth(const std::vector<std::vector<bool>> &rows) {
        std::vector<bool> reverse(rows.back().size());
        std::reverse_copy(rows.back().begin(), rows.back().end(), reverse.begin());
        return {utils::decimalToInt(rows.back()), utils::decimalToInt(reverse)};
    }

    std::pair<int, int> calculateEast(const std::vector<std::vector<bool>> &rows) {
        std::vector<bool> row;
        for (int k = 0; k < 10; ++k) {
            row.push_back(rows[k].back());
        }
        std::vector<bool> reverse(rows.back().size());
        std::reverse_copy(row.begin(), row.end(), reverse.begin());
        return {utils::decimalToInt(row), utils::decimalToInt(reverse)};
    }

    std::pair<int, int> calculateWest(const std::vector<std::vector<bool>> &rows) {
        std::vector<bool> row;
        for (int k = 0; k < 10; ++k) {
            row.push_back(rows[k].front());
        }
        std::vector<bool> reverse(rows.back().size());
        std::reverse_copy(row.begin(), row.end(), reverse.begin());
        return {utils::decimalToInt(row), utils::decimalToInt(reverse)};
    }

    std::pair<int, int> calculateDefault(const std::vector<std::vector<bool>> &rows) {
        return {-1, -1};
    }

    template<typename T>
    void rotate90(std::vector<std::vector<T>> &tile) {
        std::vector<std::vector<T>> tmp(tile.size(), std::vector<T>(tile.size(), T()));
        for (int k = 0; k < tile.size(); ++k) {
            for (int p = 0; p < tile.size(); ++p) {
                tmp[k][p] = tile[tile.size() - 1 - p][k];
            }
        }
        tile = tmp;
    }

    template<typename T>
    void moveHorizontal(std::vector<std::vector<T>> &tile) {
        for (int i = 0; i < tile.size(); ++i) {
            for (int j = 0; j < tile.size() / 2; ++j) {
                std::swap(tile[i][j], tile[i][tile.size() - 1 - j]);
            }
        }
    }

    template<typename T>
    void moveVertical(std::vector<std::vector<T>> &tile) {
        for (int i = 0; i < tile.size(); ++i) {
            for (int j = 0; j < tile.size() / 2; ++j) {
                std::swap(tile[j][i], tile[tile.size() - 1 - j][i]);
            }
        }
    }

    bool match(std::pair<int, int> a, std::pair<int, int> b) {
        return a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second;
    }

    bool match(int a, std::pair<int, int> b) {
        return a == b.first || a == b.second;
    }

    bool isMatching(std::pair<int, int> value, const std::vector<std::vector<bool>> &tile) {
        return match(value, calculateNorth(tile)) || match(value, calculateSouth(tile)) ||
               match(value, calculateEast(tile)) || match(value, calculateWest(tile));
    }

    bool isMatching(int value, const std::vector<std::vector<bool>> &tile) {
        return match(value, calculateNorth(tile)) || match(value, calculateSouth(tile)) ||
               match(value, calculateEast(tile)) || match(value, calculateWest(tile)) || (value < 0);
    }

    int findEdge(const std::vector<Tile> &tiles, int edge, int secondEdge = -1) {
        for (int k = 0; k < tiles.size(); ++k) {
            if (!tiles[k].found) {
                if (isMatching(edge, tiles[k].rows) && isMatching(secondEdge, tiles[k].rows)) {
                    return k;
                }
            }
        }
        assert("edge not found");
        return -1;
    }

    void findSeaMonsters(std::vector<std::vector<std::pair<bool, bool>>> &map) {
        for (int i = 0; i < map.size() - seaMonster.size(); ++i) {
            for (int j = 0; j < map.size() - seaMonster[0].size(); ++j) {
                bool seaMonsterFound = true;
                for (int x = 0; x < seaMonster.size(); ++x) {
                    for (int y = 0; y < seaMonster[0].size(); ++y) {
                        if (seaMonster[x][y] && !map[i + x][j + y].first) {
                            seaMonsterFound = false;
                        }
                    }
                }
                if (seaMonsterFound) {
                    for (int x = 0; x < seaMonster.size(); ++x) {
                        for (int y = 0; y < seaMonster[0].size(); ++y) {
                            if (seaMonster[x][y]) {
                                map[i + x][j + y].second = true;
                            }
                        }
                    }
                }
            }
        }
    }

    typedef std::pair<int, int> (*calculateEdge)(const std::vector<std::vector<bool>> &rows);

    void arrangeTile(std::vector<Tile> &tiles, int index, calculateEdge calculateFunction, int edge,
                     calculateEdge calculateFunction2 = calculateDefault, int edge2 = -1) {
        int k = 0;
        while (k < 4 &&
               (calculateFunction(tiles[index].rows).first != edge ||
                calculateFunction2(tiles[index].rows).first != edge2)) {
            rotate90<bool>(tiles[index].rows);
            k++;
        }
        if (calculateFunction(tiles[index].rows).first == edge &&
            calculateFunction2(tiles[index].rows).first == edge2) {
            return;
        }

        moveHorizontal<bool>(tiles[index].rows);
        k = 0;
        while (k < 4 && (calculateFunction(tiles[index].rows).first != edge ||
                         calculateFunction2(tiles[index].rows).first != edge2)) {
            rotate90<bool>(tiles[index].rows);
            k++;
        }
        if (calculateFunction(tiles[index].rows).first == edge &&
            calculateFunction2(tiles[index].rows).first == edge2) {
            return;
        } else {
            moveHorizontal<bool>(tiles[index].rows);
        }

        moveVertical<bool>(tiles[index].rows);
        k = 0;
        while (k < 4 && (calculateFunction(tiles[index].rows).first != edge ||
                         calculateFunction2(tiles[index].rows).first != edge2)) {
            rotate90<bool>(tiles[index].rows);
            k++;
        }
        if (calculateFunction(tiles[index].rows).first == edge &&
            calculateFunction2(tiles[index].rows).first == edge2) {
            return;
        } else {
            moveVertical<bool>(tiles[index].rows);
        }

        moveVertical<bool>(tiles[index].rows);
        moveHorizontal<bool>(tiles[index].rows);
        k = 0;
        while (k < 4 && (calculateFunction(tiles[index].rows).first != edge ||
                         calculateFunction2(tiles[index].rows).first != edge2)) {
            rotate90<bool>(tiles[index].rows);
            k++;
        }
        if (calculateFunction(tiles[index].rows).first == edge &&
            calculateFunction2(tiles[index].rows).first == edge2) {
            return;
        } else {
            moveHorizontal<bool>(tiles[index].rows);
            moveVertical<bool>(tiles[index].rows);
        }
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        struct Tile {
            int id;
            std::vector<std::vector<bool>> rows;
        };
        std::vector<Tile> tiles;

        // Convert all edges (backwards and forwards) to binary
        // the solution will be the 4 tiles that have 2 unique values.
        for (int i = 0; i < input.size(); i = i + 12) {
            Tile currentTile;
            currentTile.id = std::stoi(input[i].substr(5, 4));
            std::vector<std::vector<bool>> currentRows;
            for (int j = i + 1; j < i + 11; ++j) {
                std::vector<bool> row;
                for (const auto &c : input[j]) {
                    row.push_back(c == '#');
                }
                currentRows.emplace_back(row);
            }
            currentTile.rows = currentRows;
            tiles.emplace_back(currentTile);
        }

        unsigned long long prod = 1;
        for (int i = 0; i < tiles.size(); ++i) {
            int nr = 0;
            std::vector<std::pair<int, int>> edges{calculateNorth(tiles[i].rows), calculateSouth(tiles[i].rows),
                                                   calculateEast(tiles[i].rows), calculateWest(tiles[i].rows)};
            for (const auto &edge : edges) {
                bool found = false;
                for (int j = 0; j < tiles.size() && !found; ++j) {
                    if (i != j) {
                        if (isMatching(edge, tiles[j].rows)) {
                            found = true;
                        }
                    }
                }
                if (found) {
                    nr++;
                }
            }
            if (nr == 2) {
                prod *= tiles[i].id;
            }
        }

        return prod;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<Tile> tiles;
        // Convert all edges (backwards and forwards) to binary
        // the solution will be the 4 tiles that have 2 unique values.
        for (int i = 0; i < input.size(); i = i + 12) {
            Tile currentTile;
            currentTile.id = std::stoi(input[i].substr(5, 4));
            std::vector<std::vector<bool>> currentRows;
            for (int j = i + 1; j < i + 11; ++j) {
                std::vector<bool> row;
                for (const auto &c : input[j]) {
                    row.push_back(c == '#');
                }
                currentRows.emplace_back(row);
            }
            currentTile.rows = currentRows;
            currentTile.found = false;
            tiles.emplace_back(currentTile);
        }

        std::vector<std::vector<int>> map(sqrt(tiles.size()), std::vector<int>(sqrt(tiles.size()), -1));
        for (int i = 0; i < tiles.size(); ++i) {
            std::vector<std::pair<int, bool>> edges{{calculateNorth(tiles[i].rows).first, false},
                                                    {calculateEast(tiles[i].rows).first,  false},
                                                    {calculateSouth(tiles[i].rows).first, false},
                                                    {calculateWest(tiles[i].rows).first,  false}};
            for (int k = 0; k < edges.size(); ++k) {
                for (int j = 0; j < tiles.size(); ++j) {
                    if (i != j) {
                        if (isMatching(edges[k].first, tiles[j].rows)) {
                            edges[k].second = true;
                            break;
                        }
                    }
                }
            }
            if (std::count_if(edges.begin(), edges.end(), [](const auto &edge) {
                return edge.second == true;
            }) == 2) {
                map[0][0] = i;
                tiles[i].found = true;
                int nrRotation = 0;
                if (edges[0].second) {
                    if (edges[3].second) {
                        nrRotation = 2;
                    }
                    nrRotation = 1;
                } else if (edges[2].second && edges[3].second) {
                    nrRotation = 3;
                }
                for (int k = 0; k < nrRotation; ++k) {
                    rotate90(tiles[i].rows);
                }
                break;
            }
        }

        for (int i = 1; i < map.size(); ++i) {
            auto east = calculateEast(tiles[map[0][i - 1]].rows).first;
            int foundIndex = findEdge(tiles, east);
            tiles[foundIndex].found = true;
            map[0][i] = foundIndex;
            arrangeTile(tiles, foundIndex, calculateWest, east);
        }

        for (int i = 1; i < map.size(); ++i) {
            auto south = calculateSouth(tiles[map[i - 1][0]].rows).first;
            int foundIndex = findEdge(tiles, south);
            tiles[foundIndex].found = true;
            map[i][0] = foundIndex;
            arrangeTile(tiles, foundIndex, calculateNorth, south);
            for (int j = 1; j < map.size(); ++j) {
                auto south = calculateSouth(tiles[map[i - 1][j]].rows).first;
                auto east = calculateEast(tiles[map[i][j - 1]].rows).first;
                int foundIndex = findEdge(tiles, south, east);
                tiles[foundIndex].found = true;
                map[i][j] = foundIndex;
                arrangeTile(tiles, foundIndex, calculateNorth, south, calculateWest, east);
            }
        }

        int size = map.size() * (tiles[0].rows.size() - 2);
        int N = tiles[0].rows.size() - 2;
        std::vector<std::vector<std::pair<bool, bool>>> finalMap(size, std::vector<std::pair<bool, bool>>(size, {false,
                                                                                                                 false}));

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map.size(); ++j) {
                for (int k = 1; k < tiles[0].rows.size() - 1; ++k) {
                    for (int p = 1; p < tiles[0].rows.size() - 1; ++p) {
                        finalMap[i * N + k - 1][j * N + p - 1].first = tiles[map[i][j]].rows[k][p];
                    }
                }
            }
        }

        {
            for (int k = 0; k < 4; ++k) {
                findSeaMonsters(finalMap);
                rotate90<std::pair<bool, bool>>(finalMap);
            }
        }
        {
            moveHorizontal<std::pair<bool, bool>>(finalMap);
            for (int k = 0; k < 4; ++k) {
                findSeaMonsters(finalMap);
                rotate90<std::pair<bool, bool>>(finalMap);
            }
            moveHorizontal<std::pair<bool, bool>>(finalMap);
        }
        {
            moveVertical<std::pair<bool, bool>>(finalMap);
            for (int k = 0; k < 4; ++k) {
                findSeaMonsters(finalMap);
                rotate90<std::pair<bool, bool>>(finalMap);
            }
            moveVertical<std::pair<bool, bool>>(finalMap);
        }
        {
            moveHorizontal<std::pair<bool, bool>>(finalMap);
            moveVertical<std::pair<bool, bool>>(finalMap);
            for (int k = 0; k < 4; ++k) {
                findSeaMonsters(finalMap);
                rotate90<std::pair<bool, bool>>(finalMap);
            }
            moveVertical<std::pair<bool, bool>>(finalMap);
            moveHorizontal<std::pair<bool, bool>>(finalMap);
        }

        int count = 0;
        for (int i = 0; i < finalMap.size(); ++i) {
            for (int j = 0; j < finalMap[0].size(); ++j) {
                if (finalMap[i][j].first && !finalMap[i][j].second) {
                    count++;
                }
            }
        }

        return count;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day20::part_1("../2020/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day20::part_2("../2020/day20/input.in") << std::endl;

    return 0;
}
#endif
