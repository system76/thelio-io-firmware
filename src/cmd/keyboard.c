#include <stdio.h>
#include <string.h>
#include "../cpu.h"
#include <util/delay.h>
#include "../keyboard/hid.h"
#include "../keyboard/mod.h"
#include "../pin.h"
#include "../stdio.h"
#include "../uart.h"

#define MAX_KEYS 7

int cmd_keyboard(int argc, char ** argv) {
    printf("reading keypresses. CTRL-C to exit\n");

    struct Uart * uart = stdio_uart;

    struct Uart * hid_uart = uart_new(0);
    uart_init(hid_uart, 9600);
    uint8_t hid_report;
    uint16_t hid;
    int hid_i;

    struct Pin * pins[KEY_PINS] = { NULL };
    int i;
    int j;

    struct Key * keys[MAX_KEYS] = { NULL };
    struct Key * key;
    int key_i = 0;

    unsigned char fn_key = 0;

    // Initialize pins
    for(i = 0; i < KEY_PINS; i++) {
        struct Pin * pin = pin_new(key_pins[i]);

        // Verify pins match names
        if (strcmp(pin->name, key_pin_names[i]) != 0){
            printf("Key pin %d: %s (%d) does not match %s\n", i, pin->name, key_pins[i], key_pin_names[i]);
            return 1;
        }

        // Set all pins to inputs with pull-ups
        pin_set_dir(pin, 0);
        pin_set(pin, 1);

        pins[i] = pin;
    }

    while(1) {
        for(key_i = 0; key_i < MAX_KEYS; key_i++) {
            keys[key_i] = NULL;
        }
        key_i = 0;
        fn_key = 0;

        // Iterate each pin, setting it to ground, then check for affected pins
        for(i = 0; i < KEY_PINS - 1; i++) {
            struct Pin * pin = pins[i];

            // Set to output, ground
            pin_set_dir(pin, 1);
            pin_set(pin, 0);

            _delay_us(1);

            // Iterate all other pins, checking for grounding inputs
            for(j = i + 1; j < KEY_PINS; j++) {
                struct Pin * other = pins[j];

                // Check if pin is grounded
                if(pin_get(other) == 0) {
                    key = key_new(i, j);
                    if (key != NULL) {
                        printf("%s\n", key->name ? key->name : "UNKNOWN");
                        if (key->hid == KEY_FN) {
                            // Function key
                            fn_key = 1;
                        } else if (key_i < sizeof(keys)) {
                            keys[key_i] = key;
                            key_i++;
                        }
                    } else {
                        printf("%d, %d key not found\n", i, j);
                    }
                }
            }

            // Reset to input with pull-up
            pin_set_dir(pin, 0);
            pin_set(pin, 1);
        }

        // Evaluate keys for each HID report
        for(hid_report = 0; hid_report < 3; hid_report++) {
            // Write the report number
            uart_write(hid_uart, hid_report + 1);

            hid_i = 0;

            // Write each key that is of the correct hid type
            for(key_i = 0; key_i < MAX_KEYS; key_i++) {
                hid = 0;

                key = keys[key_i];
                if (key != NULL) {
                    hid = fn_key ? key->fn_hid : key->hid;
                }

                if (hid != 0 && (uint8_t)(hid >> 8) == hid_report) {
                    printf("HID %d, %d: %X\n", hid_report + 1, hid_i, (uint8_t)hid);
                    uart_write(hid_uart, (uint8_t)hid);
                    hid_i ++;
                }
            }

            // Write the remainder of the descriptor
            for(; hid_i < MAX_KEYS; hid_i++) {
                uart_write(hid_uart, 0);
            }
        }

        // Exit if ctrl-c is pressed
        if (uart_can_read(uart)) {
            char c = uart_read(uart);
            if (c == 3) {
                break;
            }
        }
    }

    return 0;
}
