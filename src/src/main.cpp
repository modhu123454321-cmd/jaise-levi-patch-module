#include <stdio.h>

__attribute__((constructor))
void mod_init() {
    printf("[CursorIndicator] preload-native library loaded\n");
}
