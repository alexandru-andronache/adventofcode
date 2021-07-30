#include "math_util.h"
#include <utility>
#include <cmath>

namespace math {

    __int128_t modularInverse(__int128_t a, __int128_t b)
    {
        __int128_t b0 = b;
        __int128_t aa = 1, ba = 0;
        while (true)
        {
            __int128_t q = a / b;
            if (a == b * q)
            {
                if (b != 1)
                {
                    // Modular inverse does not exist!
                    return -1;
                }
                while (ba < 0) ba += b0;
                return ba;
            }
            __int128_t tmp_a = a;
            __int128_t tmp_aa = aa;
            a = b;
            b = tmp_a - b * q;
            aa = ba;
            ba = tmp_aa - ba * q;
        }
    }

    __int128_t mod(__int128_t a, __int128_t b) {
        return (a >= 0) ? (a % b) : (b + a % b);
    }

    __int128_t modular_power(__int128_t a, __int128_t p, __int128_t m) {
        __int128_t res = 1;
        while (p > 0) {
            if (p % 2 == 1) {
                res = math::mod(res * a, m);
            }
            a = math::mod(a * a, m);
            p = p / 2;
        }
        return res;
    }

    __int128_t modular_divide(__int128_t a, __int128_t b, __int128_t m) {
        a = math::mod(a, m);
        __int128_t inv = math::modularInverse(b, m);
        return (inv == -1) ? -1 : (a * inv) % m;
    }

    bool coliniar(int x1, int y1, int x2, int y2, int x3, int y3) {
        return x2 * y3 + x3 * y1 + x1 * y2 - y1 * x2 - x3 * y2 - x1 * y3 == 0;
    }

    std::pair<long long, long long> solvequadratic(double a, double b, double c) {
        if (a == 0) {
            if (b == 0) {
                if (c == 0) {
                    return {0, 0};
                }
                return {-1, -1};
            }
            double x = (-c) / b;
            if (roundl(x) == x) {
                return {x, -1};
            }
            return {-1, -1};
        }
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            return {-1, -1};
        }
        if (delta == 0) {
            double x = (-b) / (2 * a);
            if (roundl(x) == x) {
                return {x, -1};
            }
            return {-1, -1};
        }
        float x = sqrt(delta);
        long long x1 = -1;
        long long x2 = -1;
        if (x * x == delta) {
            double y = (-b - x) / (2 * a);
            if (roundl(y) == y) {
                x1 = (-b - x) / (2 * a);
            }
            y = (-b + x) / (2 * a);
            if (roundl(y) == y) {
                x2 = (-b + x) / (2 * a);
            }
        }
        return {x1, x2};
    }
}