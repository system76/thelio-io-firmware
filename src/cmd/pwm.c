#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pin.h"
#include "../stdio.h"
#include "../uart.h"

int cmd_pwm(int argc, char ** argv) {
    if (argc > 1) {
        struct Pin * pin = pin_from_name(argv[1]);

        if (pin == NULL) {
            printf("pin '%s' not found\n", argv[1]);
            return 1;
        }

        if(argc > 2) {
            // Set direction to output
            pin_set_dir(pin, 1);

            // Set to off
            pin_set(pin, 0);

            int pwm = atoi(argv[2]);

            if (pwm < 0 || pwm > 100) {
                printf("pwm '%d' from input '%s' not in %d..%d\n", pwm, argv[2], 0, 100);
                return 1;
            }

            printf("PWM on pin %s at %d%%. Press CTRL-C to exit.\n", pin->name, pwm);

            struct Uart * uart = stdio_uart;

            int step = 0;
            while(1) {
                if (step <= 0) {
                    step = 100;
                }
                step--;
                if (step < pwm) {
                    pin_set(pin, 1);
                } else {
                    pin_set(pin, 0);
                }

                if (uart_can_read(uart)) {
                    char c = uart_read(uart);
                    if (c == 3) {
                        break;
                    }
                }
            }

            pin_set(pin, 0);
        } else {
            printf("no pwm provided in %d..%d\n", 0, 100);
            return 1;
        }
    } else {
        printf("no pin provided in %d..%d\n", 0, pin_count() - 1);
        return 1;
    }

    return 0;
}
