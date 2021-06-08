#include <vector>
#include <deque>
#include <map>

namespace intcode {
    template <class T>
    class IntCode {
    public:
        struct exitState {
            T returnValue;
            T startIndex;
            bool halt;
            bool needInput;
        };

        IntCode(const std::vector<T>& v, const std::deque<T>& inputID, T index = 0) {
            inputIDs = inputID;
            startIndex = index;
            for (int i = 0; i < v.size(); ++i) {
                values[i] = v[i];
            }
            relativeBase = 0;
            output = 0;
        }
        exitState advance() {
            T i = startIndex;
            while (i < values.size()) {
                if (values[i] % 10 == 1) {
                    T value1 = getValue(i, 1);
                    T value2 = getValue(i, 2);
                    setValue(i, 3, value1 + value2);
                    i = i + 4;
                } else if (values[i] % 10 == 2) {
                    T value1 = getValue(i, 1);
                    T value2 = getValue(i, 2);
                    setValue(i, 3, value1 * value2);
                    i = i + 4;
                } else if (values[i] % 10 == 3) {
                    if (inputIDs.size() > 0) {
                        setValue(i, 1, inputIDs.front());
                        inputIDs.pop_front();
                        i = i + 2;
                    }
                    else {
                        startIndex = i;
                        return {output, startIndex, false, true};
                    }
                } else if (values[i] % 10 == 4) {
                    output = getValue(i, 1);
                    i = i + 2;
                    startIndex = i;
                    return {output, i, false, false};
                } else if (values[i] % 10 == 5) {
                    long long value = getValue(i, 1);
                    long long value2 = getValue(i, 2);
                    if (value != 0) {
                        i = value2;
                    }
                    else {
                        i = i + 3;
                    }
                } else if (values[i] % 10 == 6) {
                    long long value = getValue(i, 1);
                    long long value2 = getValue(i, 2);
                    if (value == 0) {
                        i = value2;
                    }
                    else {
                        i = i + 3;
                    }
                } else if (values[i] % 10 == 7) {
                    long long value1 = getValue(i, 1);
                    long long value2 = getValue(i, 2);
                    if (value1 < value2) {
                        setValue(i, 3, 1);
                    } else {
                        setValue(i, 3, 0);
                    }
                    i = i + 4;
                } else if (values[i] % 10 == 8) {
                    long long value1 = getValue(i, 1);
                    long long value2 = getValue(i, 2);
                    if (value1 == value2) {
                        setValue(i, 3, 1);
                    } else {
                        setValue(i, 3, 0);
                    }
                    i = i + 4;
                }
                else if (values[i] % 10 == 9 && values[i] != 99) {
                    long long value1 = getValue(i, 1);
                    relativeBase += value1;
                    i = i + 2;
                }
                else if (values[i] == 99) {
                    startIndex = i;
                    return {output, i, true, false};
                }
            }
            startIndex = i;
            return {output, i, true, false};
        }

        std::deque<T> inputIDs;
        T startIndex;
        std::map<T, T> values;
        T relativeBase;
        T output = 0;

        T getMode(T nr, T index) {
            if (index == 1) return (nr / 100) % 10;
            if (index == 2) return (nr / 1000) % 10;
            if (index == 3) return nr / 10000;
            return 0;
        }
        T getValue(T array_index, T index) {
            if (getMode(values[array_index], index) == 1) {
                return values[array_index + index];
            }
            if (getMode(values[array_index], index) == 2) {
                return values[values[array_index + index] + relativeBase];
            }
            return values[values[array_index + index]];
        }
        void setValue(T array_index, T index, T value) {
            if (getMode(values[array_index], index) == 1) {
                values[array_index + index] = value;
            }
            else if (getMode(values[array_index], index) == 2) {
                values[values[array_index + index] + relativeBase] = value;
            } else {
                values[values[array_index + index]] = value;
            }
        }
    };
}
