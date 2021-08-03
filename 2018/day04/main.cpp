#include "file.h"
#include <iostream>
#include <vector>
#include <map>

namespace aoc2018_day04 {
    struct Date {
        int year;
        int month;
        int day;
        int hour;
        int minute;
    };

    enum class Action {
        beginShift, fallsAsleep, wakeUp
    };

    struct Record {
        Date date;
        Action action;
        int id;
    };

    constexpr int MINUTES = 60;

    void processAndSortRecords(std::vector<Record>& input) {
        std::sort(input.begin(), input.end(), [] (const Record& a, const Record&b) {
            if (a.date.year != b.date.year)
                return a.date.year < b.date.year;
            if (a.date.month != b.date.month)
                return a.date.month < b.date.month;
            if (a.date.day != b.date.day)
                return a.date.day < b.date.day;
            if (a.date.hour != b.date.hour)
                return a.date.hour < b.date.hour;
            return a.date.minute < b.date.minute;
        });
    }

    int findGuardWithMostMinuteAsleep(const std::vector<Record>& input) {
        auto it = input.begin();
        std::map<int, int> timeSleep;
        while (it != input.end()) {
            if (it->action == Action::beginShift) {
                int id = it->id;
                it++;
                while (it != input.end() && it->action != Action::beginShift) {
                    int begin = 0, end = 59;
                    if (it->action == Action::fallsAsleep) {
                        if (it->date.hour == 0) {
                            begin = it->date.minute;
                        }
                        it++;
                    }
                    if (it->action == Action::wakeUp) {
                        if (it->date.hour == 0) {
                            end = it->date.minute;
                        }
                        it++;
                    }
                    if (timeSleep.find(id) != timeSleep.end()) {
                        timeSleep[id] += end - begin;
                    }
                    else {
                        timeSleep.insert(std::pair<int, int>(id, end - begin));
                    }
                }
            }
        }
        int max = 0, id = 0;
        for (const auto& p : timeSleep) {
            if (max < p.second) {
                max = p.second;
                id = p.first;
            }
        }

        return id;
    }

    int findMinuteMostSleepForGuard(const std::vector<Record>& input, int id) {
        auto it = input.begin();
        std::vector<int> minutes(MINUTES, 0);
        while (it != input.end()) {
            if (it->action == Action::beginShift && it->id == id) {
                it++;
                while (it != input.end() && it->action != Action::beginShift) {
                    int begin = 0, end = 59;
                    if (it->action == Action::fallsAsleep) {
                        if (it->date.hour == 0) {
                            begin = it->date.minute;
                        }
                        it++;
                    }
                    if (it->action == Action::wakeUp) {
                        if (it->date.hour == 0) {
                            end = it->date.minute;
                        }
                        it++;
                    }
                    for (int i = begin; i < end; ++i) {
                        minutes[i]++;
                    }
                }
            }
            it++;
        }

        int minute = 0, max = 0;
        for (int i = 0; i < MINUTES; ++i) {
            if (max < minutes[i]) {
                max = minutes[i];
                minute = i;
            }
        }
        return minute;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " -[]:#");
        std::vector<Record> input;
        for (const auto& line : lines) {
            Action action;
            if (line[5].compare("falls") == 0) {
                action = Action::fallsAsleep;
            }
            else if (line[5].compare("wakes") == 0) {
                action = Action::wakeUp;
            }
            else {
                action = Action::beginShift;
            }
            input.push_back({std::stoi(line[0]),
                             std::stoi(line[1]),
                             std::stoi(line[2]),
                             std::stoi(line[3]),
                             std::stoi(line[4]),
                             action,
                             action == Action::beginShift ? std::stoi(line[6]) : 0,
                             });
        }
        processAndSortRecords(input);

        int guardId = findGuardWithMostMinuteAsleep(input);
        return guardId * findMinuteMostSleepForGuard(input, guardId);
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<std::string>> lines = file::readFileAndSplit(path, " -[]:#");
        std::vector<Record> input;
        for (const auto& line : lines) {
            Action action;
            if (line[5].compare("falls") == 0) {
                action = Action::fallsAsleep;
            }
            else if (line[5].compare("wakes") == 0) {
                action = Action::wakeUp;
            }
            else {
                action = Action::beginShift;
            }
            input.push_back({std::stoi(line[0]),
                             std::stoi(line[1]),
                             std::stoi(line[2]),
                             std::stoi(line[3]),
                             std::stoi(line[4]),
                             action,
                             action == Action::beginShift ? std::stoi(line[6]) : 0,
                             });
        }
        processAndSortRecords(input);

        auto it = input.begin();
        std::map<int, std::vector<int>> timeSleep;
        while (it != input.end()) {
            if (it->action == Action::beginShift) {
                int id = it->id;
                it++;
                while (it != input.end() && it->action != Action::beginShift) {
                    int begin = 0, end = 59;
                    if (it->action == Action::fallsAsleep) {
                        if (it->date.hour == 0) {
                            begin = it->date.minute;
                        }
                        it++;
                    }
                    if (it->action == Action::wakeUp) {
                        if (it->date.hour == 0) {
                            end = it->date.minute;
                        }
                        it++;
                    }
                    if (timeSleep.find(id) == timeSleep.end()) {
                        timeSleep.insert(std::pair<int, std::vector<int>>(id, std::vector<int>(MINUTES, 0)));
                    }

                    for (int i = begin; i < end; ++i) {
                        timeSleep[id][i]++;
                    }
                }
            }
        }
        int guardId = 0, max = 0, minuteId = 0;
        for (const auto& t : timeSleep) {
            for (int i = 0; i < MINUTES; ++i) {
                if (max < t.second[i]) {
                    max = t.second[i];
                    guardId = t.first;
                    minuteId = i;
                }
            }
        }

        return guardId * minuteId;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day04::part_1("../2018/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day04::part_2("../2018/day04/input.in") << std::endl;

    return 0;
}
#endif
