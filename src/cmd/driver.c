#include <stdio.h>
#include <string.h>
#include "../cpu.h"
#include <util/delay.h>
#include "../battery.h"
#include "../keyboard/mod.h"
#include "../macro.h"
#include "../pin.h"
#include "../stdio.h"
#include "../uart.h"

int cmd_driver(int argc, char ** argv) {
    printf("Running driver. CTRL-C to exit\n");

    struct Pin * pins[KEY_PINS] = { NULL };
    // 276 = 1 + 2 + 3 ... + 23
    unsigned char map[512] = { 0 };
    int map_i;

    // Initialize pins
    int i;
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

    struct Battery battery = battery_new(0x0B);

    uint16_t bat_data;
    int bat_i = 0;

    struct Uart * uart = stdio_uart;

    while(1) {
        // Iterate each pin, setting it to ground, then check for affected pins
        map_i = 0;
        for(i = 0; i < KEY_PINS - 1; i++) {
            struct Pin * pin = pins[i];

            // Set to output, ground
            pin_set_dir(pin, 1);
            pin_set(pin, 0);

            _delay_us(1);

            // Iterate all other pins, checking for grounding inputs
            int j;
            for(j = i + 1; j < KEY_PINS; j++) {
                struct Pin * other = pins[j];

                if (map_i >= sizeof(map)) {
                    printf("Map index %d is out of range 0..%d", map_i, sizeof(map));
                    return 1;
                }

                // Check if pin is grounded
                if(pin_get(other) == 0) {
                    if (map[map_i]) {
                        //printf("%d hold\n", map_i);
                        map[map_i] = 2;
                    } else {
                        //printf("k %s 1\n", key_name(i, j));
                        map[map_i] = 1;
                    }
                } else if (map[map_i]) {
                    //printf("k %s 0\n", key_name(i, j));
                    map[map_i] = 0;
                }

                map_i += 1;
            }

            // Reset to input with pull-up
            pin_set_dir(pin, 0);
            pin_set(pin, 1);
        }

        if (bat_i % 1024 == 0) {
            bat_i = 0;

            #define BAT_PROP(N) \
                if(battery_ ## N(&battery, &bat_data) == 0) { \
                    printf("b %s %d\n", str(N), bat_data); \
                }

            BAT_PROP(temp)

            BAT_PROP(voltage)
            BAT_PROP(current)

            BAT_PROP(capacity)
            BAT_PROP(full_capacity)

            BAT_PROP(cycle_count)

            BAT_PROP(design_capacity)
            BAT_PROP(design_voltage)
        }

        bat_i++;

        if (uart_can_read(uart)) {
            char c = uart_read(uart);
            if (c == 3) {
                break;
            }
        }
    }

    return 0;
}
