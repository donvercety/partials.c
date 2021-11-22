#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen

/* Pointer to an array
 * -------------------
 * You can generate a pointer to the first element of an array
 * by simply specifying the array name, without any index.
 */

void reverse(char *str_p) {
    int c, i, j;
    for(i = 0, j = strlen(str_p) -1; i < j; i++, j--){
        c = str_p[i];
        str_p[i] = str_p[j];
        str_p[j] =  c;
    }
}

int main() {
    char str[] = "The quick brown fox jumps over the lazy dog!";
    char *str_p = str;
    
    printf("%s\n", str);
    reverse(str_p);
    printf("%s", str);
}
