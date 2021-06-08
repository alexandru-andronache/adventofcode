#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2020_day25 {
    unsigned long long part_1(unsigned long long publicKeyCard,
                              unsigned long long publicKeyDoor,
                              unsigned long long modulo = 20201227) {
        unsigned long long valueCard = 1;
        const unsigned long long subject = 7;
        int loopCard = 0;
        while (valueCard != publicKeyCard) {
            valueCard = valueCard * subject;
            valueCard = valueCard % modulo;
            loopCard++;
        }
        unsigned long long valueDoor = 1;
        int loopDoor = 0;
        while (valueDoor != publicKeyDoor) {
            valueDoor = valueDoor * subject;
            valueDoor = valueDoor % modulo;
            loopDoor++;
        }

        unsigned long long encryptionKey = 1;
        unsigned subjectNumber = publicKeyDoor;
        for (int i = 0; i < loopCard; ++i) {
            encryptionKey = encryptionKey * subjectNumber;
            encryptionKey = encryptionKey % modulo;
        }
        return encryptionKey;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day25::part_1(9789649, 3647239) << std::endl;
    return 0;
}
#endif
