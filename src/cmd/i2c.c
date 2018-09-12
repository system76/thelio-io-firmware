#include <stdio.h>
#include <stdlib.h>
#include "../i2c/master.h"

#define MIN_CHIP 0x03
#define MAX_CHIP 0x77

#define MIN_DATA 0x00
#define MAX_DATA 0xFF

#define MIN_VALUE 0x00
#define MAX_VALUE 0xFF

int cmd_i2c(int argc, char ** argv) {
    if (argc > 1) {
        int chip = strtol(argv[1], NULL, 16);
        if (chip < MIN_CHIP || chip > MAX_CHIP) {
            printf("chip address '0x%X' from input '%s' not in 0x%X..0x%X\n", (unsigned int)chip, argv[1], MIN_CHIP, MAX_CHIP);
            return 1;
        }

        if (argc > 2) {
            int data = strtol(argv[2], NULL, 16);
            if (data < MIN_DATA || data > MAX_DATA) {
                printf("data address '0x%X' from input '%s' not in 0x%X..0x%X\n", (unsigned int)data, argv[2], MIN_DATA, MAX_DATA);
                return 1;
            }

            if (argc > 3) {
                int value = strtol(argv[3], NULL, 16);
                if (value < MIN_VALUE || value > MAX_VALUE){
                    printf("value '0x%X' from input '%s' not in 0x%X..0x%X\n", (unsigned int)value, argv[3], MIN_VALUE, MAX_VALUE);
                    return 1;
                }

                printf("set 0x%X 0x%X 0x%X\n", (unsigned int)chip, (unsigned int)data, (unsigned int)value);

                uint8_t buf[1] = { (uint8_t)value };
                uint8_t status = i2c_set(chip, data, buf, 1);
                if(status != 0) {
                    printf("error %d\n", status);
                    return 1;
                }
            } else {
                printf("get 0x%X 0x%X\n", (unsigned int)chip, (unsigned int)data);

                uint8_t buf[1] = { 0 };
                uint8_t status = i2c_get(chip, data, buf, 1);
                if(status != 0) {
                    printf("error %d\n", status);
                    return 1;
                }
                
                printf("= 0x%X\n", buf[0]);
            }
        } else {
            printf("no data address provided in 0x%X..0x%X\n", MIN_DATA, MAX_DATA);
            return 1;
        }
    } else {
        printf("no chip address provided in 0x%X..0x%X\n", MIN_CHIP, MAX_CHIP);
        return 1;
    }

    return 0;
}
