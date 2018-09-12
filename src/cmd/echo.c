#include <stdio.h>

int cmd_echo(int argc, char ** argv) {
    int i;
    for (i = 1; i < argc; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%s", argv[i]);
    }
    printf("\n");
    return 0;
}
