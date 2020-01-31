#include <string.h>

void charfix(char *str) {
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void stread(char *str, int s) {
    fgets(str, s, stdin);
    charfix(str);
}
