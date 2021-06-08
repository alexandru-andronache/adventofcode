#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <vector>

namespace aoc2020_day16 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        struct range {
            range(int a, int b, int c, int d) {
                x1 = a;
                y1 = b;
                x2 = c;
                y2 = d;
            }

            int x1, y1, x2, y2;
        };
        std::vector<range> possibleRanges;
        int index = 0;
        while (!input[index].empty()) {
            std::vector<std::string> w = utils::splitString(input[index], ":  -");
            if (utils::isInteger(w[1])) {
                possibleRanges.emplace_back(std::stoi(w[1]), std::stoi(w[2]), std::stoi(w[4]), std::stoi(w[5]));
            } else {
                possibleRanges.emplace_back(std::stoi(w[2]), std::stoi(w[3]), std::stoi(w[5]), std::stoi(w[6]));
            }
            index++;
        }

        index += 5;

        int sum = 0;
        while (index < input.size()) {
            std::vector<std::string> w = utils::splitString(input[index], ",");
            std::vector<std::vector<int>> ticket(possibleRanges.size(), std::vector<int>());
            for (int k = 0; k < w.size(); ++k) {
                int y = std::stoi(w[k]);
                for (int i = 0; i < possibleRanges.size(); ++i) {
                    if ((possibleRanges[i].x1 <= y && possibleRanges[i].y1 >= y) ||
                        (possibleRanges[i].x2 <= y && possibleRanges[i].y2 >= y)) {
                        ticket[k].push_back(i);
                    }
                }
            }

            for (int i = 0; i < ticket.size(); ++i) {
                if (ticket[i].size() == 0) {
                    sum += std::stoi(w[i]);
                }
            }
            index++;
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        struct range {
            range(int a, int b, int c, int d) {
                x1 = a;
                y1 = b;
                x2 = c;
                y2 = d;
            }

            int x1, y1, x2, y2;
        };
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<range> possibleRanges;
        int index = 0;
        while (!input[index].empty()) {
            std::vector<std::string> w = utils::splitString(input[index], ":  -");
            if (utils::isInteger(w[1])) {
                possibleRanges.emplace_back(std::stoi(w[1]), std::stoi(w[2]), std::stoi(w[4]), std::stoi(w[5]));
            } else {
                possibleRanges.emplace_back(std::stoi(w[2]), std::stoi(w[3]), std::stoi(w[5]), std::stoi(w[6]));
            }
            index++;
        }

        index += 2;
        std::vector<int> your_ticket = utils::splitStringToInt(input[index], ",");
        index += 3;

        int indexTickets = index;

        std::vector<int> valid_tickets;
        std::vector<std::vector<int>> tickets_int;
        int k = 0;
        while (index < input.size()) {
            std::vector<std::string> w = utils::splitString(input[index], ",");
            std::vector<std::vector<int>> ticket(possibleRanges.size(), std::vector<int>());
            for (int k = 0; k < w.size(); ++k) {
                int y = std::stoi(w[k]);
                for (int i = 0; i < possibleRanges.size(); ++i) {
                    if ((possibleRanges[i].x1 <= y && possibleRanges[i].y1 >= y) ||
                        (possibleRanges[i].x2 <= y && possibleRanges[i].y2 >= y)) {
                        ticket[k].push_back(i);
                    }
                }
            }

            bool valid = true;
            for (int i = 0; i < ticket.size(); ++i) {
                if (ticket[i].size() == 0) {
                    valid = false;
                }
            }
            if (valid) {
                valid_tickets.push_back(k);
            }
            k++;
            std::vector<int> p;
            for (const auto &l : w) {
                p.push_back(std::stoi(l));
            }
            tickets_int.emplace_back(p);
            index++;
        }


        std::vector<std::vector<int>> classes(possibleRanges.size(), std::vector<int>());

        for (int i = 0; i < tickets_int[0].size(); ++i) {
            std::vector<int> r(possibleRanges.size(), 0);
            for (int j = 0; j < valid_tickets.size(); ++j) {
                for (int k = 0; k < possibleRanges.size(); ++k) {
                    if ((tickets_int[valid_tickets[j]][i] >= possibleRanges[k].x1 &&
                         tickets_int[valid_tickets[j]][i] <= possibleRanges[k].y1) ||
                        (tickets_int[valid_tickets[j]][i] >= possibleRanges[k].x2 &&
                         tickets_int[valid_tickets[j]][i] <= possibleRanges[k].y2)) {
                        r[k]++;
                    }
                }
            }
            for (int j = 0; j < r.size(); ++j) {
                if (r[j] == valid_tickets.size()) {
                    classes[i].push_back(j);
                }
            }
        }

        bool shouldContinue = true;
        while (shouldContinue) {
            shouldContinue = false;
            for (int i = 0; i < classes.size(); ++i) {
                if (classes[i].size() == 1) {
                    int x = classes[i][0];
                    for (int j = 0; j < classes.size(); ++j) {
                        if (i != j) {
                            if (std::find(classes[j].begin(), classes[j].end(), x) != classes[j].end()) {
                                shouldContinue = true;
                                classes[j].erase(std::remove(classes[j].begin(), classes[j].end(), x),
                                                 classes[j].end());
                            }
                        }
                    }
                }
            }
        }

        long long pred = 1;
        for (int i = 0; i < classes.size(); ++i) {
            if (classes[i][0] >= 0 && classes[i][0] <= 5) {
                pred = pred * your_ticket[i];
            }
        }

        return pred;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day16::part_1("../2020/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day16::part_2("../2020/day16/input.in") << std::endl;

    return 0;
}
#endif
