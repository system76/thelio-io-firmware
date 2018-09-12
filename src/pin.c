#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "macro.h"
#include "pin.h"

#define PORT_BLOCK(BLOCK) \
    {"P" xstr(BLOCK) "0", 0, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "1", 1, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "2", 2, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "3", 3, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "4", 4, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "5", 5, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "6", 6, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}, \
    {"P" xstr(BLOCK) "7", 7, &DDR ## BLOCK, &PIN ## BLOCK, &PORT ## BLOCK}

#if defined(__AVR_ATmega32U4__)
    static struct Pin PINS[] = {
        // 0x00
        PORT_BLOCK(B),
        // 0x08
        PORT_BLOCK(C),
        // 0x10
        PORT_BLOCK(D),
        // 0x18
        PORT_BLOCK(E),
        // 0x20
        PORT_BLOCK(F),
    };
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    static struct Pin PINS[] = {
        // 0x00
        PORT_BLOCK(A),
        // 0x08
        PORT_BLOCK(B),
        // 0x10
        PORT_BLOCK(C),
        // 0x18
        PORT_BLOCK(D),
        // 0x20
        PORT_BLOCK(E),
        // 0x28
        PORT_BLOCK(F),
        // 0x30
        PORT_BLOCK(G),
        // 0x38
        PORT_BLOCK(H),
        // 0x40
        PORT_BLOCK(J),
        // 0x48
        PORT_BLOCK(K),
        // 0x50
        PORT_BLOCK(L),
    };
#else
    #error "Could not find pin definitions"
#endif

int pin_count() {
    return sizeof(PINS)/sizeof(struct Pin);
}

struct Pin * pin_new(int num) {
    if (num < pin_count()) {
        return &PINS[num];
    } else {
        return NULL;
    }
}

struct Pin * pin_from_name(char * name) {
    int num;
    for (num = 0; num < pin_count(); num++) {
        struct Pin * pin = &PINS[num];
        if (strcmp(pin->name, name) == 0) {
            return pin;
        }
    }
    return NULL;
}

unsigned char pin_get_dir(struct Pin * pin) {
    if (*pin->ddr & (1 << pin->shift)) {
        return 1;
    } else {
        return 0;
    }
}

void pin_set_dir(struct Pin * pin, unsigned char value) {
    if (value) {
        *pin->ddr |= (1 << pin->shift);
    } else {
        *pin->ddr &= ~(1 << pin->shift);
    }
}

unsigned char pin_get(struct Pin * pin) {
    if (*pin->pin & (1 << pin->shift)) {
        return 1;
    } else {
        return 0;
    }
}

void pin_set(struct Pin * pin, unsigned char value) {
    if (value) {
        *pin->port |= (1 << pin->shift);
    } else {
        *pin->port &= ~(1 << pin->shift);
    }
}
