#include "file.h"
#include "intcode.h"
#include <iostream>

namespace aoc2019_day23 {
    struct packet {
        unsigned long long x {0};
        unsigned long long y {0};
    };

    unsigned long long part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        std::vector<intcode::IntCode<unsigned long long>> computers(50, {input, {}});
        std::vector<std::vector<packet>> packets(50);

        for (int i = 0; i < 50; ++i) {
            computers[i].inputIDs.push_back(i);
        }

        while (true) {
            for (int i = 0; i < 50; ++i) {
                auto exit = computers[i].advance();
                while (!exit.needInput && !exit.halt) {
                    unsigned long long id = exit.returnValue;
                    packet p;
                    p.x = computers[i].advance().returnValue;
                    p.y = computers[i].advance().returnValue;

                    if (id == 255) {
                        return p.y;
                    }
                    else if (id < 50) {
                        packets[id].push_back(p);
                    }
                    exit = computers[i].advance();
                }
            }

            for (int i = 0; i < 50; ++i) {
                for (const auto& p : packets[i]) {
                    computers[i].inputIDs.push_back(p.x);
                    computers[i].inputIDs.push_back(p.y);
                }
                packets[i].clear();
            }
            for (int i = 0; i < 50; ++i) {
                if (computers[i].inputIDs.empty()) {
                    computers[i].inputIDs.push_back(-1);
                }
            }
        }
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        std::vector<intcode::IntCode<unsigned long long>> computers(50, {input, {}});
        std::vector<std::vector<packet>> packets(50);
        packet NAT;
        unsigned long long formerNATy = 0;

        for (int i = 0; i < 50; ++i) {
            computers[i].inputIDs.push_back(i);
            computers[i].advance();
            computers[i].inputIDs.push_back(-1);
        }

        while (true) {
            for (int i = 0; i < 50; ++i) {
                auto exit = computers[i].advance();
                while (!exit.needInput && !exit.halt) {
                    unsigned long long id = exit.returnValue;
                    packet p;
                    p.x = computers[i].advance().returnValue;
                    p.y = computers[i].advance().returnValue;

                    if (id == 255) {
                        NAT = p;
                    }
                    else if (id < 50) {
                        packets[id].push_back(p);
                    }
                    exit = computers[i].advance();
                }
            }

            for (int i = 0; i < 50; ++i) {
                for (const auto& p : packets[i]) {
                    computers[i].inputIDs.push_back(p.x);
                    computers[i].inputIDs.push_back(p.y);
                }
                packets[i].clear();
            }
            bool idle = true;
            for (const auto& c : computers) {
                if (!c.inputIDs.empty()) {
                    idle = false;
                }
            }
            for (const auto& p : packets) {
                if (!p.empty()) {
                    idle = false;
                }
            }
            if (idle) {
                if (formerNATy == NAT.y) {
                    return formerNATy;
                }
                formerNATy = NAT.y;
                computers[0].inputIDs.push_back(NAT.x);
                computers[0].inputIDs.push_back(NAT.y);
            }
            for (int i = 0; i < 50; ++i) {
                if (computers[i].inputIDs.empty()) {
                    computers[i].inputIDs.push_back(-1);
                }
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day23::part_1("../2019/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day23::part_2("../2019/day23/input.in") << std::endl;

    return 0;
}
#endif
