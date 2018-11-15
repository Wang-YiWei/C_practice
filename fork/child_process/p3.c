#include<stdio.h>
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(){
    printf(ANSI_COLOR_MAGENTA"Hello , this is p3\n"ANSI_COLOR_RESET);

    return 0;
}