//
// Created by Alexandru Andronache  on 04/12/2019.
//

#pragma once
#include <vector>

namespace aoc2017_day25 {
    struct movement {
        int value;
        int direction; // -1 for left, 1 for right
        char nextState;
    };

    struct state{
        char name;
        std::vector<movement> cases;
    };

    int part_1(const std::vector<state>& states, int steps = 12173597);
}