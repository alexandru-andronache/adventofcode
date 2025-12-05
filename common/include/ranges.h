#pragma once
#include <vector>

namespace aoc {
    template<typename T>
    class Ranges {
    public:
        Ranges() = default;
        ~Ranges() = default;

        void addRange(T start, T end) {
            mRanges.emplace_back(start, end);
            merge();
        }
        bool isInRange(T value) const {
            for (const auto& range : mRanges) {
                if (value >= range.first && value <= range.second) {
                    return true;
                }
            }
            return false;
        }
        [[nodiscard]] unsigned long long count() const {
            unsigned long long count = 0;
            for (const auto& range : mRanges) {
                count += (range.second - range.first + 1);
            }
            return count;
        }

    private:
        void merge() {
            bool notFinished = true;
            while (notFinished) {
                notFinished = false;
                std::vector<std::pair<T , T >> newRanges;
                for (const auto& range : mRanges) {
                    bool added = false;
                    for (auto& newRange : newRanges) {
                        if (range.first >= newRange.first && range.second <= newRange.second) {
                            notFinished = true;
                            added = true;
                            break;
                        }
                        if (range.first <= newRange.first && range.second >= newRange.first && range.second <= newRange.second) {
                            newRange.first = range.first;
                            notFinished = true;
                            added = true;
                            break;
                        }
                        if (range.first >= newRange.first && range.first <= newRange.second && range.second >= newRange.second) {
                            newRange.second = range.second;
                            notFinished = true;
                            added = true;
                            break;
                        }
                        if (range.first <= newRange.second && range.second >= newRange.second) {
                            newRange.first = range.first;
                            newRange.second = range.second;
                            notFinished = true;
                            added = true;
                            break;
                        }
                    }
                    if (!added) {
                        newRanges.push_back(range);
                    }
                }
                mRanges = newRanges;
            }
        }

        std::vector<std::pair<T, T>> mRanges;
    };
}