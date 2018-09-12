#include <stdio.h>

#define KEY_PINS 26

struct Key {
    char * name;
    uint16_t hid;
    uint16_t fn_hid;
    int i;
    int j;
};

extern const char * key_pin_names[KEY_PINS];
extern int key_pins[KEY_PINS];

extern struct Key key_map[];

struct Key * key_new(int i, int j);
