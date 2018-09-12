#include <stdio.h>
#include "../time.h"

int cmd_time(int argc, char ** argv) {
    uint64_t time = time_get();

    uint32_t seconds = (uint32_t)(time / 1000000ULL);
    uint32_t micros = (uint32_t)(time % 1000000ULL);

    printf("%ld.%06ld\n", seconds, micros);

    return 0;
}
