#include "mod.h"

#define FLIP_H 0
#define FLIP_V 0

#if FLIP_V && FLIP_H
const char * key_pin_names[KEY_PINS] = {
    // 42 - 49 - L block
    //"PL0", "PL1",
    //"PL2", "PL3",
    "PL4", "PL5",
    "PL6", "PL7",

    // 38 - 41 - Not a block :(yyiufgnhdjydjydjydjydj
    "PG0", "PG1",
    "PG2", "PD7",

    // 30 - 27 - C block
    "PC0", "PC1",
    "PC2", "PC3",
    "PC4", "PC5",
    "PC6", "PC7",

    // 22 - 29 - A block
    "PA7", "PA6",
    "PA5", "PA4",
    "PA3", "PA2",
    "PA1", "PA0",

    "PL2", "PL3",
};

int key_pins[KEY_PINS] = {
    // 42 - 49 - L block
    //0x50, 0x51,
    //0x52, 0x53,
    0x54, 0x55,
    0x56, 0x57,

    // 38 - 41 - Not a block :(
    0x30, 0x31,
    0x32, 0x1F,

    // 30 - 27 - C block
    0x10, 0x11,
    0x12, 0x13,
    0x14, 0x15,
    0x16, 0x17,

    // 22 - 29, A block
    0x07, 0x06,
    0x05, 0x04,
    0x03, 0x02,
    0x01, 0x00,

    0x52, 0x53,
};
#elif FLIP_V
const char * key_pin_names[KEY_PINS] = {
    // 22 - 29 - A block
    "PA1", "PA0",
    "PA3", "PA2",
    "PA5", "PA4",
    "PA7", "PA6",

    // 30 - 27 - C block
    "PC6", "PC7",
    "PC4", "PC5",
    "PC2", "PC3",
    "PC0", "PC1",

    // 38 - 41 - Not a block :(
    "PG2", "PD7",
    "PG0", "PG1",

    // 42 - 49 - L block
    "PL6", "PL7",
    "PL4", "PL5",
    //"PL3", "PL2",
    //"PL1", "PL0"

    "PL3", "PL2",
};

int key_pins[KEY_PINS] = {
    // 22 - 29, A block
    0x01, 0x00,
    0x03, 0x02,
    0x05, 0x04,
    0x07, 0x06,

    // 30 - 27 - C block
    0x16, 0x17,
    0x14, 0x15,
    0x12, 0x13,
    0x10, 0x11,

    // 38 - 41 - Not a block :(
    0x32, 0x1F,
    0x30, 0x31,

    // 42 - 49 - L block
    0x56, 0x57,
    0x54, 0x55,
    //0x53, 0x52,
    //0x51, 0x50

    0x53, 0x52,
};
#elif FLIP_H
const char * key_pin_names[KEY_PINS] = {
    // 42 - 49 - L block
    //"PL1", "PL0"
    //"PL3", "PL2",
    "PL5", "PL4",
    "PL7", "PL6",

    // 38 - 41 - Not a block :(
    "PG1", "PG0",
    "PD7", "PG2",

    // 30 - 27 - C block
    "PC1", "PC0",
    "PC3", "PC2",
    "PC5", "PC4",
    "PC7", "PC6",

    // 22 - 29 - A block
    "PA6", "PA7",
    "PA4", "PA5",
    "PA2", "PA3",
    "PA0", "PA1",

    "PL3", "PL2",
};

int key_pins[KEY_PINS] = {
    // 42 - 49 - L block
    //0x51, 0x50
    //0x53, 0x52,
    0x55, 0x54,
    0x57, 0x56,

    // 38 - 41 - Not a block :(
    0x31, 0x30,
    0x1F, 0x32,

    // 30 - 27 - C block
    0x11, 0x10,
    0x13, 0x12,
    0x15, 0x14,
    0x17, 0x16,

    // 22 - 29, A block
    0x06, 0x07,
    0x04, 0x05,
    0x02, 0x03,
    0x00, 0x01,

    0x53, 0x52,
};
#else
const char * key_pin_names[KEY_PINS] = {
    // 22 - 29 - A block
    "PA0", "PA1",
    "PA2", "PA3",
    "PA4", "PA5",
    "PA6", "PA7",

    // 30 - 27 - C block
    "PC7", "PC6",
    "PC5", "PC4",
    "PC3", "PC2",
    "PC1", "PC0",

    // 38 - 41 - Not a block :(
    "PD7", "PG2",
    "PG1", "PG0",

    // 42 - 49 - L block
    "PL7", "PL6",
    "PL5", "PL4",
    //"PL3", "PL2",
    //"PL1", "PL0"

    "PL3", "PL2",
};

int key_pins[KEY_PINS] = {
    // 22 - 29, A block
    0x00, 0x01,
    0x02, 0x03,
    0x04, 0x05,
    0x06, 0x07,

    // 30 - 27 - C block
    0x17, 0x16,
    0x15, 0x14,
    0x13, 0x12,
    0x11, 0x10,

    // 38 - 41 - Not a block :(
    0x1F, 0x32,
    0x31, 0x30,

    // 42 - 49 - L block
    0x57, 0x56,
    0x55, 0x54,
    //0x53, 0x52,
    //0x51, 0x50

    0x53, 0x52,
};
#endif
