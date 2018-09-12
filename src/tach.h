#ifndef TACH_H
#define TACH_H

#include <stdint.h>

struct Tach {
    uint64_t timeout;
    uint64_t time;
    uint16_t count;
    uint16_t value;
};

struct Tach tach_new(uint64_t timeout);

uint16_t tach_step(struct Tach * tach, uint64_t time, uint16_t value);

#endif // TACH_H
