#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include "../i2c/slave.h"

#define MIN_CHIP 0x03
#define MAX_CHIP 0x77

void cmd_i2c_slave_new() {
    printf("New transaction\n");
}

void cmd_i2c_slave_recv(uint8_t data) {
    printf("Got 0x%X\n", (unsigned int)data);
}

uint8_t cmd_i2c_slave_send() {
    uint8_t data = 0x42;
    printf("Sending 0x%X\n", data);
    return data;
}

int cmd_i2c_slave(int argc, char ** argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "on") == 0) {
            if (argc > 2) {
                int chip = strtol(argv[2], NULL, 16);
                if (chip < MIN_CHIP || chip > MAX_CHIP) {
                    printf("chip address '0x%X' from input '%s' not in 0x%X..0x%X\n", (unsigned int)chip, argv[2], MIN_CHIP, MAX_CHIP);
                    return 1;
                }

                printf("entering slave mode for address 0x%X\n", (unsigned int)chip);

                i2c_slave_init(chip, cmd_i2c_slave_new, cmd_i2c_slave_recv, cmd_i2c_slave_send);
            } else {
                printf("no chip address provided in 0x%X..0x%X\n", MIN_CHIP, MAX_CHIP);
                return 1;
            }
        } else if (strcmp(argv[1], "off") == 0) {
            printf("exiting slave mode\n");

            i2c_slave_stop();
        } else {
            printf("must specify either on or off\n");
            return 1;
        }
    } else if (TWCR & (1<<TWEA)) {
        printf("running in slave mode at address 0x%X\n", TWAR >> 1);
    } else {
        printf("not running in slave mode\n");
    }

    return 0;
}
