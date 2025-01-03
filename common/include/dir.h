#pragma once

namespace direction {
    class direction {
    public:
        direction() = default;
        direction(const int x, const int y) : x(x), y(y) {}

        [[nodiscard]] int getX() const {return x;}
        [[nodiscard]] int getY() const {return y;}

        [[nodiscard]] bool isHorizontal() const {
            return x == 0;
        }
    private:
        int x, y;
    };

    static direction UP = {-1, 0};
    static direction DOWN = {1, 0};
    static direction LEFT = {0, 1};
    static direction RIGHT = {0, -1};

    inline direction getDirection(const char c) {
        if (c == '<') return RIGHT;
        if (c == '>') return LEFT;
        if (c == '^') return UP;
        if (c == 'v') return DOWN;
        return {0, 0};
    }
}
