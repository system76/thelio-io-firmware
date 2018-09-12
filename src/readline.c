#include <stdio.h>

int readline(char * buf, int len) {
    int escape = 0;
    int i = 0;
    while (i < len) {
        char c = getchar();
        if (escape == 2) {
            // Throw away CSI codes
            if (c >= 0x40 || c <= 0x7E) {
                escape = 0;
            }
        } else if (escape == 1) {
            // Throw away escape codes, detect CSI codes
            if (c == '[') {
                escape = 2;
            } else {
                escape = 0;
            }
        } else if (c == 0x1B) {
            // Detect escape codes
            escape = 1;
        } else if (c == 0x7F) {
            // Handle backspace
            if(i > 0) {
                i -= 1;
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
        } else if(c == 3) {
            // Break on CTRL-C
            putchar('\r');
            putchar('\n');
            return 0;
        } else if(c == '\r' || c == '\n') {
            // Return on enter
            putchar('\r');
            putchar('\n');
            break;
        } else if(c == '\t') {
            // Ignore tab
        } else {
            putchar(c);
            buf[i] = c;
            i += 1;
        }
    }
    return i;
}
