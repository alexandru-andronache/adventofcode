#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <set>

namespace aoc2022_day15 {
    struct data {
        utils::point sensor;
        utils::point beacon;
        int dist;
    };

    std::pair<int, unsigned long long> solve(const std::vector<data>& points, int row) {
        std::vector<std::pair<int, int>> ranges;
        std::pair<int, unsigned long long> sol{0, 0};

        for (const auto& point : points) {
            int dist = utils::manhattanDistance(point.beacon.x, point.beacon.y, point.sensor.x, point.sensor.y);
            if (dist >= std::abs(point.sensor.x - row)) {
                int dist_x = dist - std::abs(point.sensor.x - row);
                bool intersect = false;
                int start = point.sensor.y - dist_x;
                int end = point.sensor.y + dist_x;
                for (auto& r : ranges) {
                    if (r.first <= start && start <= r.second) {
                        intersect = true;
                        if (r.first <= end && end <= r.second) {
                            intersect = true;
                        }
                        else {
                            r.second = end;
                        }
                    }
                    else if (r.first <= end && end <= r.second) {
                        r.first = start;
                        intersect = true;
                    }
                    else if (start <= r.first && r.first <= end) {
                        r.first = start;
                        r.second = end;
                        intersect = true;
                    }
                }

                if (!intersect) {
                    ranges.emplace_back(start, end);
                }

                bool unique = false;
                while (!unique) {
                    unique = true;
                    int index = -1;
                    for (int i = 0; i < ranges.size() - 1; ++i) {
                        if (ranges[i].first <= ranges[i + 1].first && ranges[i + 1].first <= ranges[i].second) {
                            if (ranges[i + 1].second <= ranges[i].second) {
                                unique = false;
                                index = i + 1;
                                break;
                            }
                            else if (ranges[i + 1].second > ranges[i].second) {
                                ranges[i].second = ranges[i + 1].second;
                                unique = false;
                                index = i + 1;
                                break;
                            }
                        }
                        else if (ranges[i].first <= ranges[i + 1].second && ranges[i + 1].second <= ranges[i].second) {
                            if (ranges[i + 1].first >= ranges[i].first) {
                                unique = false;
                                index = i + 1;
                                break;
                            }
                            else if (ranges[i + 1].first < ranges[i].first) {
                                ranges[i].first = ranges[i + 1].first;
                                unique = false;
                                index = i + 1;
                                break;
                            }
                        }
                        else if (ranges[i + 1].first <= ranges[i].first && ranges[i].second <= ranges[i + 1].second) {
                            ranges[i].first = ranges[i + 1].first;
                            ranges[i].second = ranges[i + 1].second;
                            unique = false;
                            index = i + 1;
                            break;
                        }
                    }
                    if (index != -1) {
                        ranges.erase(ranges.begin() + index);
                    }
                }
            }
        }

        for (const auto& r : ranges) {
            sol.first += r.second - r.first + 1;
        }

        std::sort(ranges.begin(), ranges.end(), [](const auto& r1, const auto& r2) {
            if (r1.first < r2.first) {
                return true;
            }
            if (r1.first > r2.first) {
                return false;
            }
            if (r1.second < r2.second) {
                return true;
            }
            return false;
        });

        for (int k = 0; k < ranges.size() - 1; ++k) {
            if (ranges[k].second + 1 < ranges[k + 1].first) {
                sol.second= (ranges[k].second + 1) * 4000000ULL + row;
            }
        }

        return sol;
    }

    int part_1(std::string_view path, int row) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<data> points;
        std::vector<std::pair<int, int>> ranges;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, " =,:");
            points.push_back({{std::stoi(t[5]), std::stoi(t[3])},
                              {std::stoi(t[13]), std::stoi(t[11])}});
        }

        auto sol = solve(points, row);

        std::set<int> unique;
        for (const auto& p : points) {
            if (p.sensor.x == row) {
                unique.insert(p.sensor.y);
            }
            if (p.beacon.x == row) {
                unique.insert(p.beacon.y);
            }
        }

        return sol.first - unique.size();
    }

    unsigned long long part_2(std::string_view path, int size) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> ranges;
        std::vector<data> points;
        for (const auto& l : input) {
            std::vector<std::string> t = utils::splitString(l, " =,:");
            points.push_back({{std::stoi(t[5]), std::stoi(t[3])},
                              {std::stoi(t[13]), std::stoi(t[11])}});
        }

        for (int row = 0; row <= size; ++row) {
            ranges.clear();
            for (const auto& point : points) {
                int dist = utils::manhattanDistance(point.beacon.x, point.beacon.y, point.sensor.x,point.sensor.y);
                if (dist >= std::abs(point.sensor.x - row)) {
                    int dist_x = dist - std::abs(point.sensor.x - row);
                    bool intersect = false;
                    int start = point.sensor.y - dist_x;
                    int end = point.sensor.y + dist_x;
                    for (auto &r: ranges) {
                        if (r.first <= start && start <= r.second) {
                            intersect = true;
                            if (r.first <= end && end <= r.second) {
                                intersect = true;
                            } else {
                                r.second = end;
                            }
                        } else if (r.first <= end && end <= r.second) {
                            r.first = start;
                            intersect = true;
                        } else if (start <= r.first && r.first <= end) {
                            r.first = start;
                            r.second = end;
                            intersect = true;
                        }
                    }

                    if (!intersect) {
                        ranges.emplace_back(start, end);
                    }

                    bool unique = false;
                    while (!unique) {
                        unique = true;
                        int index = -1;
                        for (int i = 0; i < ranges.size() - 1; ++i) {
                            if (ranges[i].first <= ranges[i + 1].first && ranges[i + 1].first <= ranges[i].second) {
                                if (ranges[i + 1].second <= ranges[i].second) {
                                    unique = false;
                                    index = i + 1;
                                    break;
                                } else if (ranges[i + 1].second > ranges[i].second) {
                                    ranges[i].second = ranges[i + 1].second;
                                    unique = false;
                                    index = i + 1;
                                    break;
                                }
                            } else if (ranges[i].first <= ranges[i + 1].second &&
                                       ranges[i + 1].second <= ranges[i].second) {
                                if (ranges[i + 1].first >= ranges[i].first) {
                                    unique = false;
                                    index = i + 1;
                                    break;
                                } else if (ranges[i + 1].first < ranges[i].first) {
                                    ranges[i].first = ranges[i + 1].first;
                                    unique = false;
                                    index = i + 1;
                                    break;
                                }
                            } else if (ranges[i + 1].first <= ranges[i].first &&
                                       ranges[i].second <= ranges[i + 1].second) {
                                ranges[i].first = ranges[i + 1].first;
                                ranges[i].second = ranges[i + 1].second;
                                unique = false;
                                index = i + 1;
                                break;
                            }
                        }
                        if (index != -1) {
                            ranges.erase(ranges.begin() + index);
                        }
                    }
                }
            }

            std::sort(ranges.begin(), ranges.end(), [](const auto& r1, const auto& r2) {
                if (r1.first < r2.first) {
                    return true;
                }
                if (r1.first > r2.first) {
                    return false;
                }
                if (r1.second < r2.second) {
                    return true;
                }
                return false;
            });

            for (int k = 0; k < ranges.size() - 1; ++k) {
                if (ranges[k].second + 1 < ranges[k + 1].first) {
                    return (ranges[k].second + 1) * 4000000ULL + row;
                }
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day15::part_1("../2022/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2022_day15::part_2("../2022/day15/input.in") << std::endl;

    return 0;
}
#endif
