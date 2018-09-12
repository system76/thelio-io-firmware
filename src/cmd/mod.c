#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mod.h"
#include "../tokenize.h"

#undef CMD
#define CMD(N) int cmd_ ## N(int argc, char ** argv);

CMDS

#undef CMD
#define CMD(N) { #N, cmd_ ## N },

struct command commands[] = {
    CMDS
    { NULL, NULL }
};

void run(char * line) {
    int line_len = strlen(line);
    char * line_copy = malloc(line_len);
    if (line_copy == NULL) {
        printf("run: failed to allocate\n");
        return;
    }

    strcpy(line_copy, line);

    char * cmds[8] = { NULL };
    int cmds_len = tokenize(';', line_copy, line_len, cmds, 7);
    cmds[cmds_len] = NULL;

    int cmd_i;
    for(cmd_i = 0; cmd_i < cmds_len; cmd_i++) {
        char * cmd = cmds[cmd_i];
        int cmd_len = strlen(cmd);

        char * argv[8] = { NULL };
        int argc = tokenize(' ', cmd, cmd_len, argv, 7);

        if (argc > 0) {
            int i;
            for (i = 0; ; i++) {
                char * name = commands[i].name;
                if(name == NULL) {
                    printf("unknown command: '%s'\n", argv[0]);
                    break;
                }
                if (strcmp(argv[0], name) == 0) {
                    commands[i].func(argc, argv);
                    break;
                }
            }
        }
    }

    free(line_copy);
}
