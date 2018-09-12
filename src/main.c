#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "cmd/mod.h"
//#include "i2c/mod.h"
#include "macro.h"
#include "readline.h"
#include "stdio.h"
#include "time.h"
#include "uart.h"

int cmd_thelio(int argc, char ** argv);

int main(){
    stdio_init(0, 1000000);
    time_init();
    //i2c_init();
    sei();

    cmd_thelio(0, NULL);

    // for (;;) {
    //     printf("io@%s> ", xstr(__DEVICE__));
    //
    //     char line[64] = { 0 };
    //     int line_len = readline(line, 63);
    //     line[line_len] = 0;
    //
    //     run(line);
    // }

    return 0;
}
