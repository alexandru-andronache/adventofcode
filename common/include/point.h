#pragma once

#include "dir.h"

namespace point {
    class point {
    public:
        point() = default;
        point(const int x, const int y) : x(x), y(y) {}

        point& operator+=(const direction::direction& rhs) {
            x += rhs.getX();
            y += rhs.getY();
            return *this;
        }

        friend point operator+(point lhs, const direction::direction& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        [[nodiscard]] int getX() const {return x;}
        [[nodiscard]] int getY() const {return y;}

        auto operator<=>(const point&) const = default;
    private:
        int x, y;
    };
}