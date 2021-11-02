#include <stdio.h>
#include "fx.h"

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("arg: %d, value: %s\n", i, argv[i]);
    }

    print_hex();
    return 0;
}