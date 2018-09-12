#ifndef PIN_H
#define PIN_H

#include <stdint.h>

struct Pin {
    char * name;
    int shift;
    volatile uint8_t * ddr;
    volatile uint8_t * pin;
    volatile uint8_t * port;
};

int pin_count();
struct Pin * pin_new(int num);
struct Pin * pin_from_name(char * name);

unsigned char pin_get_dir(struct Pin * pin);
void pin_set_dir(struct Pin * pin, unsigned char value);

unsigned char pin_get(struct Pin * pin);
void pin_set(struct Pin * pin, unsigned char value);

#endif // PIN_H
