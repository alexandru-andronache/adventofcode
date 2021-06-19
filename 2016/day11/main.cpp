#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <array>

namespace aoc2016_day11 {
    template<size_t N>
    bool isValid(const std::pair<std::bitset<N>, std::bitset<N>>& floor) {
        if (floor.second.none()) {
            return true;
        }
        for (int i = 0; i < N; ++i) {
            if (floor.first.test(i) && !floor.second.test(i)) {
                return false;
            }
        }
        return true;
    }

    template <size_t N>
    std::array<std::pair<int, int>, N> transform(const std::vector<std::pair<std::bitset<N>, std::bitset<N>>>& state) {
        std::array<std::pair<int, int>, N> t;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < state.size(); ++j) {
                if (state[j].first.test(i)) {
                    t[i].first = j;
                }
                if (state[j].second.test(i)) {
                    t[i].second = j;
                }
            }
        }
        std::sort(t.begin(), t.end(), [](const auto& a, const auto& b){
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second < b.second;
        });

        return t;
    }

    template<size_t N>
    int solve(const std::vector<std::pair<std::bitset<N>, std::bitset<N>>>& floors) {
        std::vector<std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>>> states;
        states.emplace_back(0, floors);
        std::array<std::set<std::array<std::pair<int, int>, N>>, 4> previousStates;

        previousStates[states[0].first].insert(transform(states[0].second));

        int steps = 0;

        while (true) {
            std::vector<std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>>> newStates;

            for (const auto& state : states) {
                if (state.first == 3 &&
                state.second[0].first.none() && state.second[0].second.none() &&
                state.second[1].first.none() && state.second[1].second.none() &&
                state.second[2].first.none() && state.second[2].second.none()) {
                    return steps;
                }
            }

            // chip(1) can't stay with other generators(2) if his generator is not there
            for (const auto& state : states) {
                int floor = state.first;

                std::bitset<N> chipFloors = state.second[floor].first;
                std::bitset<N> generatorFloors = state.second[floor].second;
                // can go up?
                if (floor < 3) {
                    // can i take 2 up?
                    bool canITake2Up = false;
                    if (chipFloors.count() + generatorFloors.count() >= 2) {
                        for (int i = 0; i < N; ++i) {
                            if (chipFloors.test(i) && generatorFloors.test(i)) {
                                //bring up i chip and i genereator
                                // this configuration will be valid
                                // needs to test if it's unique
                                std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                tmp = state;
                                tmp.first = floor + 1;
                                tmp.second[floor].first.flip(i);
                                tmp.second[floor].second.flip(i);
                                tmp.second[floor + 1].first.flip(i);
                                tmp.second[floor + 1].second.flip(i);

                                std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                if (previousStates[tmp.first].count(t) == 0) {
                                    canITake2Up = true;
                                    previousStates[tmp.first].insert(t);
                                    newStates.push_back(tmp);
                                }
                            }
                        }

                        // next 2 chips or 2 generators

                        for (int i = 0; i < N; ++i) {
                            for (int j = i + 1; j < N; ++j) {
                                if (chipFloors.test(i) && chipFloors.test(j)) {
                                    std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                    tmp = state;
                                    tmp.first = floor + 1;
                                    tmp.second[floor].first.flip(i);
                                    tmp.second[floor].first.flip(j);
                                    tmp.second[floor + 1].first.flip(i);
                                    tmp.second[floor + 1].first.flip(j);

                                    std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                    if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                        canITake2Up = true;
                                        previousStates[tmp.first].insert(t);
                                        newStates.push_back(tmp);
                                    }
                                }
                            }
                        }

                        for (int i = 0; i < N; ++i) {
                            for (int j = i + 1; j < N; ++j) {
                                if (generatorFloors.test(i) && generatorFloors.test(j)) {
                                    std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                    tmp = state;
                                    tmp.first = floor + 1;
                                    tmp.second[floor].second.flip(i);
                                    tmp.second[floor].second.flip(j);
                                    tmp.second[floor + 1].second.flip(i);
                                    tmp.second[floor + 1].second.flip(j);
                                    std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                    if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                        canITake2Up = true;
                                        previousStates[tmp.first].insert(t);
                                        newStates.push_back(tmp);
                                    }
                                }
                            }
                        }

                    }
                    if (!canITake2Up) {
                        //take 1 item up

                        for (int i = 0; i < N; ++i) {
                            if (chipFloors.test(i)) {
                                std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                tmp = state;
                                tmp.first = floor + 1;
                                tmp.second[floor].first.flip(i);
                                tmp.second[floor + 1].first.flip(i);
                                std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                    canITake2Up = true;
                                    previousStates[tmp.first].insert(t);
                                    newStates.push_back(tmp);
                                }
                            }
                        }

                        for (int i = 0; i < N; ++i) {
                            if (generatorFloors.test(i)) {
                                std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                tmp = state;
                                tmp.first = floor + 1;
                                tmp.second[floor].second.flip(i);
                                tmp.second[floor + 1].second.flip(i);
                                std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                    canITake2Up = true;
                                    previousStates[tmp.first].insert(t);
                                    newStates.push_back(tmp);
                                }
                            }
                        }
                    }
                }
                // can i go down?

                bool shouldIGoDown = false;
                int k = floor - 1;
                while (k >= 0) {
                    if (state.second[k].first.any() || state.second[k].second.any()) {
                        shouldIGoDown = true;
                    }
                    k--;
                }

                if (floor > 0 && shouldIGoDown) {
                    bool canITakeOneDown = false;


                    for (int i = 0; i < N; ++i) {
                        if (chipFloors.test(i)) {
                            std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                            tmp = state;
                            tmp.first = floor - 1;
                            tmp.second[floor].first.flip(i);
                            tmp.second[floor - 1].first.flip(i);
                            std::array<std::pair<int, int>, N> t = transform(tmp.second);

                            if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                canITakeOneDown = true;
                                previousStates[tmp.first].insert(t);
                                newStates.push_back(tmp);
                            }
                        }
                    }

                    for (int i = 0; i < N; ++i) {
                        if (generatorFloors.test(i)) {
                            std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                            tmp = state;
                            tmp.first = floor - 1;
                            tmp.second[floor].second.flip(i);
                            tmp.second[floor - 1].second.flip(i);
                            std::array<std::pair<int, int>, N> t = transform(tmp.second);

                            if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                canITakeOneDown = true;
                                previousStates[tmp.first].insert(t);
                                newStates.push_back(tmp);
                            }
                        }
                    }


                    if (!canITakeOneDown) {


                        if (chipFloors.count() + generatorFloors.count() >= 2) {
                            for (int i = 0; i < N; ++i) {
                                if (chipFloors.test(i) && generatorFloors.test(i)) {
                                    //bring up i chip and i genereator
                                    // this configuration will be valid
                                    // needs to test if it's unique
                                    std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                    tmp = state;
                                    tmp.first = floor - 1;
                                    tmp.second[floor].first.flip(i);
                                    tmp.second[floor].second.flip(i);
                                    tmp.second[floor - 1].first.flip(i);
                                    tmp.second[floor - 1].second.flip(i);
                                    std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                    if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                        canITakeOneDown = true;
                                        previousStates[tmp.first].insert(t);
                                        newStates.push_back(tmp);
                                    }
                                }
                            }

                            // next 2 chips or 2 generators

                            for (int i = 0; i < N; ++i) {
                                for (int j = i + 1; j < N; ++j) {
                                    if (chipFloors.test(i) && chipFloors.test(j)) {
                                        std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                        tmp = state;
                                        tmp.first = floor - 1;
                                        tmp.second[floor].first.flip(i);
                                        tmp.second[floor].first.flip(j);
                                        tmp.second[floor - 1].first.flip(i);
                                        tmp.second[floor - 1].first.flip(j);
                                        std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                        if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                            canITakeOneDown = true;
                                            previousStates[tmp.first].insert(t);
                                            newStates.push_back(tmp);
                                        }
                                    }
                                }
                            }

                            for (int i = 0; i < N; ++i) {
                                for (int j = i + 1; j < N; ++j) {
                                    if (generatorFloors.test(i) && generatorFloors.test(j)) {
                                        std::pair<int, std::vector<std::pair<std::bitset<N>, std::bitset<N>>>> tmp;
                                        tmp = state;
                                        tmp.first = floor - 1;
                                        tmp.second[floor].second.flip(i);
                                        tmp.second[floor].second.flip(j);
                                        tmp.second[floor - 1].second.flip(i);
                                        tmp.second[floor - 1].second.flip(j);
                                        std::array<std::pair<int, int>, N> t = transform(tmp.second);

                                        if (isValid(tmp.second[floor + 1]) && previousStates[tmp.first].count(t) == 0) {
                                            canITakeOneDown = true;
                                            previousStates[tmp.first].insert(t);
                                            newStates.push_back(tmp);
                                        }
                                    }
                                }
                            }

                        }

                    }


                }
            }

            states = newStates;
            steps++;
        }
        return steps;
    }

    int part_1() {
        std::vector<std::pair<std::bitset<5>, std::bitset<5>>> floors(4);
        floors[0].first.set(0);
        floors[0].second.set(0);
        floors[0].second.set(1);
        floors[0].second.set(2);
        floors[1].first.set(1);
        floors[1].first.set(2);
        floors[2].first.set(3);
        floors[2].first.set(4);
        floors[2].second.set(3);
        floors[2].second.set(4);

        return solve(floors);
    }

    int part_2() {
        std::vector<std::pair<std::bitset<7>, std::bitset<7>>> floors(4);
        floors[0].first.set(0);
        floors[0].first.set(5);
        floors[0].first.set(6);
        floors[0].second.set(0);
        floors[0].second.set(1);
        floors[0].second.set(2);
        floors[0].second.set(5);
        floors[0].second.set(6);
        floors[1].first.set(1);
        floors[1].first.set(2);
        floors[2].first.set(3);
        floors[2].first.set(4);
        floors[2].second.set(3);
        floors[2].second.set(4);

        return solve(floors);
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day11::part_1() << std::endl;
    std::cout << "Part 2: " << aoc2016_day11::part_2() << std::endl;

    return 0;
}
#endif
