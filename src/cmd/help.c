#include <stdio.h>
#include "mod.h"

int cmd_help(int argc, char ** argv) {
    printf("Commands\n");
    int i;
    for (i = 0; ; i++) {
        char * name = commands[i].name;
        if(name == NULL) {
            break;
        }
        printf("    %s\n", commands[i].name);
    }
    return 0;
}
