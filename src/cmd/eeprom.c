#include <avr/eeprom.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __AVR_ATmega32U4__
    #define EEPROM_SIZE 1024
#else
    #error "Could not find eeprom definitions"
#endif

int cmd_eeprom(int argc, char ** argv) {
    if (argc > 1) {
        errno = 0;
        unsigned long address = strtoul(argv[1], NULL, 16);
        if (errno) {
            printf("address '%s' invalid\n", argv[1]);
            return 1;
        }
        if (address >= EEPROM_SIZE) {
            printf("address '%s' not in %x..%x\n", argv[1], 0, EEPROM_SIZE - 1);
            return 1;
        }

        uint8_t * ptr = (uint8_t *)((uint16_t)(address));
        if (argc > 2) {
            errno = 0;
            unsigned long value = strtoul(argv[2], NULL, 16);
            if (errno) {
                printf("value '%s' invalid\n", argv[2]);
                return 1;
            }
            if (value > 0xFF) {
                printf("value '%s' not in %d..%d\n", argv[2], 0, 0xFF);
                return 1;
            }

            eeprom_update_byte(ptr, (uint8_t)value);
        } else {
            uint8_t value = eeprom_read_byte(ptr);
            printf("%02X\n", value);
        }
    } else {
        uint16_t address;
        for (address = 0; address < EEPROM_SIZE; address++) {
            if (address % 16 == 0) {
                if (address != 0) {
                    printf("\n");
                }
                printf("%04X:", address);
            }

            printf(" %02X", eeprom_read_byte((uint8_t *)address));
        }

        if (address > 0) {
            printf("\n");
        }
    }

    return 0;
}
