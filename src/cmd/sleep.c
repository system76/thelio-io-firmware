#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../cpu.h"
#include <util/delay.h>

int cmd_sleep(int argc, char ** argv) {
    if (argc > 1) {
        int num = atoi(argv[1]);
        if(num < 0) {
            printf("invalid argument '%s'\n", argv[1]);
            return 1;
        } else {
            int i;
            for(i = 0; i < num; i++) {
                _delay_ms(1000);
            }
        }
    } else {
        printf("no number\n");
        return 1;
    }
    return 0;
}
