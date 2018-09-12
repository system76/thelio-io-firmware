#include <stdio.h>
#include <stdlib.h>
#include "../stdio.h"
#include "../uart.h"

int cmd_console(int argc, char ** argv) {
    if (argc > 1) {
        int num = atoi(argv[1]);
        if(num < 0) {
            printf("invalid console '%d' from input '%s' not in %d..%d\n", num, argv[1], 0, uart_count());
            return 1;
        }

        struct Uart * uart = uart_new(num);
        if (uart == NULL) {
            printf("console '%d' not found\n", num);
            return 1;
        }
        if (uart == stdio_uart) {
            printf("console '%d' is currently stdio\n", num);
            return 1;
        }

        uart_init(uart, 57600);
        while (uart_can_read(uart)) {
            uart_read(uart);
        }
        uart_write(uart, 3);

        while (1) {
            if (uart_can_read(uart)) {
                char c = uart_read(uart);
                if (c == 3) {
                    return 0;
                }
                uart_write(stdio_uart, c);
            }
            if (uart_can_read(stdio_uart)) {
                char c = uart_read(stdio_uart);
                if (c == 3) {
                    return 0;
                }
                uart_write(uart, c);
            }
        }
    } else {
        printf("no console specified\n");
        return 1;
    }

    return 0;
}
