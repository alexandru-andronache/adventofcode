#pragma once

namespace math {
    // https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    __int128_t modularInverse(__int128_t a, __int128_t b);

    /*
     * if a is positiv returns a mod b
     * if a is negativ returns a + b mod b
     */
    __int128_t mod(__int128_t a, __int128_t b);

    /*
     * returns a to the power p modulo m
     */
    __int128_t modular_power(__int128_t a, __int128_t p, __int128_t m);

    /*
     * returns a divided by b modulo m
     */
    __int128_t modular_divide(__int128_t a, __int128_t b, __int128_t m);
}
