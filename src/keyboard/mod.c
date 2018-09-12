#include <stdio.h>
#include "mod.h"

struct Key * key_new(int i, int j) {
    int name_i = 0;
    for (name_i = 0; ; name_i++) {
        struct Key * k = &key_map[name_i];
        if (k->name == NULL) {
            return NULL;
        }
        if (k->i == i && k->j == j) {
            return k;
        }
    }
}
