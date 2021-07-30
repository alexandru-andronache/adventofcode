#include "file.h"
#include "utilities.h"
#include <iostream>

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

    int part_1(const std::vector<state>& states, int steps = 12173597) {
        std::vector<int> bits(50000, 0);
        bits.push_back(0);
        auto it = bits.begin() + 25000;
        char currentState = 'A';
        for (int step = 0; step < steps; ++step) {
            movement m = states[currentState - 'A'].cases[*it];
            *it = m.value;
            it += m.direction;
            currentState = m.nextState;
        }

        int checksum = 0;
        for (const auto& b : bits) {
            checksum += b;
        }
        return checksum;
    }
}

#ifndef TESTING
int main() {
    std::vector<aoc2017_day25::state> states {{'A', {{1, 1, 'B'}, {0, -1, 'C'}}},
                               {'B', {{1, -1, 'A'}, {1, 1, 'D'}}},
                               {'C', {{1, 1, 'A'}, {0, -1, 'E'}}},
                               {'D', {{1, 1, 'A'}, {0, 1, 'B'}}},
                               {'E', {{1, -1, 'F'}, {1, -1, 'C'}}},
                               {'F', {{1, 1, 'D'}, {1, 1, 'A'}}}};

    std::cout << "Part 1: " << aoc2017_day25::part_1(states) << std::endl;
    return 0;
}
#endif
