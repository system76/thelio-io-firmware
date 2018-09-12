#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void time_init(void);
uint64_t time_get(void);
void time_set(uint64_t time);

#endif // TIME_H
