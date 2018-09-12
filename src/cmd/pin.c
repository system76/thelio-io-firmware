#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pin.h"

int cmd_pin(int argc, char ** argv) {
    if (argc > 1) {
        struct Pin * pin = pin_from_name(argv[1]);

        if (pin == NULL) {
            printf("pin '%s' not found\n", argv[1]);
            return 1;
        }

        if(argc > 2) {
            // Set direction to output
            pin_set_dir(pin, 1);

            if(strcmp(argv[2], "on") == 0) {
                printf("setting pin %s to on\n", pin->name);
                pin_set(pin, 1);
            } else if (strcmp(argv[2], "off") == 0) {
                printf("setting pin %s to off\n", pin->name);
                pin_set(pin, 0);
            } else {
                printf("provide on or off to set\n");
                return 1;
            }
        } else {
            // Set direction to input
            pin_set_dir(pin, 0);

            // Disable pull-up resistor
            pin_set(pin, 0);

            if (pin_get(pin)) {
                printf("getting pin %s: on\n", pin->name);
            } else {
                printf("getting pin %s: off\n", pin->name);
            }
        }
    } else {
        printf("no pin provided\n");
        return 1;
    }

    return 0;
}
